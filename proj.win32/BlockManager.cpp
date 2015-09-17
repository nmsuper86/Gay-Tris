#include "BlockManager.h"
#include <Windows.h>


#pragma region 系统调用

BlockManager::BlockManager()
{
	
} //BlockManager::BlockManager()

BlockManager::~BlockManager()
{

} //BlockManager::~BlockManager()

BlockManager* BlockManager::create(CCPoint p_pointToDisplayOnScreen, DisplayManger* p_displayManagerToBind)
{
	BlockManager* pRet = new BlockManager();
	if (pRet && pRet->init(p_pointToDisplayOnScreen, p_displayManagerToBind))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
} //BlockManager* BlockManager::create(CCPoint position)

bool BlockManager::init(CCPoint p_pointToDisplayOnScreen, DisplayManger* p_displayManagerToBind)
{
	bool bRet = true;
	do 
	{
		this->setPosition(p_pointToDisplayOnScreen);

		this->m_boundDisplayManager = p_displayManagerToBind;
		if (m_boundDisplayManager == NULL)
		{
			bRet = false;
			break;
		}

		CCSprite* backgroundImage = CCSprite::create("Background.png");
		if (!backgroundImage)
		{
			bRet = false;
			break;
		}
		this->addChild(backgroundImage);

		//初始化单元状态矩阵
		for (int x = 0; x < BlockManager::CellMatrixWidth; x++)
		{
			for (int y = 0; y < BlockManager::CellMatrixHeight; y++)
			{
				this->m_matrixCellState[x][y] = BlockManager::CellState::Empty;
				this->m_matrixDeadBlockSprites[x][y] = NULL;
			}
		}

		//设定默认更新频率
		this->m_periodDropping = BlockManager::DefaultRefreshTime;

		//创建第一个块
		this->m_blockWaiting = _createNewBlock();
//		this->m_blockWaiting->bindManager(this);
		this->m_blockWaiting->retain();

		//放入第一个块并创建第二个块
		this->_pushNewBlock();

		if (this->m_blockWaiting == NULL || this->m_blockDropping == NULL)
		{
			bRet = false;
			break;
		}

		//初始化已死方块批量精灵
		this->m_spriteBatchNodeDeadBlocks = CCSpriteBatchNode::create("BlockDead.png", BlockManager::CellMatrixWidth * BlockManager::CellMatrixHeight);
// 		this->m_spriteBatchNodeDeadBlocks->setAnchorPoint(ccp(0.5, 0.5));
// 		this->m_spriteBatchNodeDeadBlocks->setPosition(this->getAnchorPoint());
		if (this->m_spriteBatchNodeDeadBlocks == NULL)
		{
			bRet = false;
			break;
		}
		this->addChild(this->m_spriteBatchNodeDeadBlocks);
		
		//初始化键盘控制
		this->m_isKeyboardPressed = false;

	} while (0);

	if (bRet)
	{
		this->scheduleUpdate();
		this->_rePaintDeadBlocks();
	}
	else
	{
		if (this->m_boundDisplayManager)
		{
			this->m_boundDisplayManager->autorelease();
			this->m_boundDisplayManager = NULL;
		}

		if (this->m_spriteBatchNodeDeadBlocks)
		{
			this->m_spriteBatchNodeDeadBlocks->autorelease();
			this->m_spriteBatchNodeDeadBlocks = NULL;
		}
	}

	return bRet;

}

void BlockManager::update(float delta)
{
	if (!this->_shouldBlockTryDrop(this->m_periodDropping))
	{
		this->_donotTryDrop();
	}
	else
	{
		this->_doTryUpdateDrop();
	}
} //void BlockManager::update(float delta)

void BlockManager::triggerKeyboard(int p_valueKey)
{
	switch (p_valueKey)
	{
	case VK_LEFT:
		if (!this->m_isKeyboardPressed)
		{
			this->_doTryMove(Block::Direction::Left);
		}
		break; //case VK_LEFT

	case VK_RIGHT:
		if (!this->m_isKeyboardPressed)
		{
			this->_doTryMove(Block::Direction::Right);
		}
		break; //case VK_RIGHT

	case VK_DOWN:
		this->_doTryRequiredDrop();
		break; //case VK_DOWN

	case VK_UP:
		if (!this->m_isKeyboardPressed)
		{
			this->_doTryTurn90Degrees();
		}
		break; //case VK_UP

	default:
		break;
	}
	this->setKeyboardState(true);
} //void BlockManager::triggerKeyboard(int p_valueKey)

#pragma endregion

#pragma region 公有自定义函数

int BlockManager::getUpdateTime()
{
	return this->m_periodDropping;
} //int BlockManager::getUpdateTime()

void BlockManager::setUpdateTime(int p_updateTime)
{
	this->m_periodDropping = p_updateTime;
} //void BlockManager::setUpdateTime(int time)

CCPoint BlockManager::convertBlockPositionToPixelPosition(CCPoint p_pointBlock)
{
	CCPoint pointResult;
	pointResult.x = -BlockManager::CellMatrixWidth / 2 * Block::CellSize + p_pointBlock.x * Block::CellSize;
	pointResult.y = BlockManager::CellMatrixHeight / 2 * Block::CellSize - (p_pointBlock.y + 1) * Block::CellSize;
	return pointResult;
} //CCPoint BlockManager::convertBlockToPixel(CCPoint blockPoint)

void BlockManager::setKeyboardState(bool p_isKeyPressed)
{
	this->m_isKeyboardPressed = p_isKeyPressed;
} //void BlockManager::setKeyDownState(bool keyDownState)


#pragma endregion

#pragma region 私有自定义函数

Block* BlockManager::_createNewBlock()
{
	return Block::generateNewBlock(this);
}

void BlockManager::_pushNewBlock()
{
	this->m_blockDropping = this->m_blockWaiting;
	this->m_blockDropping->setPosition(this->convertBlockPositionToPixelPosition(ccp(BlockManager::CellMatrixWidth / 2, Block::BlockWidthCount / 2 - 1)));

	Block::CellPosition position = this->m_blockDropping->getCellPosition();
	for (int i = 0; i < 4; i++)
	{
		this->m_matrixCellState[(int)position.points[i].x][(int)position.points[i].y] = BlockManager::CellState::Dropping;
	}
	this->addChild(this->m_blockDropping);

	this->m_blockWaiting = Block::generateNewBlock(this);
	this->m_blockWaiting->retain();
	this->m_boundDisplayManager->nextBlockChanged(this->m_blockWaiting);
} //void BlockManager::_pushNewBlock()

/*******************************************************/

bool BlockManager::_shouldBlockTryDrop(int updateTime)
{
	return this->m_blockDropping->increaseTimeCounter(updateTime);
}

void BlockManager::_donotTryDrop()
{
	//Nothing
} //void BlockManager::_donotTryDrop()

void BlockManager::_doTryUpdateDrop()
{
	if (this->_currentBlockCanMove(Block::Direction::Down))
	{
		this->_currentBlockDoMove(Block::Direction::Down);
	}
	else
	{
		this->_currentBlockStopDrop();
	}
} //void BlockManager::_doTryDrop()

void BlockManager::_doTryMove(Block::Direction direction)
{
	if (this->_currentBlockCanMove(direction))
	{
		this->_currentBlockDoMove(direction);
	}
} //void BlockManager::_doTryMove(Block::Direction direction)

void BlockManager::_doTryRequiredDrop()
{
	if (!this->_shouldBlockTryDrop(BlockManager::RequiredUpdateTime))
	{
		this->_donotTryDrop();
	}
	else
	{
		this->_doTryUpdateDrop();
	}
} //void BlockManager::_doTryRequiredDrop()

void BlockManager::_doTryTurn90Degrees()
{
	Block::BlockType blockType = this->m_blockDropping->getBlockType();
	if (blockType != Block::O)
	{
		if (this->_currentBlockCanTurn90Degrees())
		{
			this->_currentBlockDoTurn90Degrees();
		}
	}
} //void BlockManager::_doTryTurn90Degrees()

/********************************************************/

bool BlockManager::_currentBlockCanMove(Block::Direction direction)
{
	Block::CellPosition position = this->m_blockDropping->getCellPosition();

	switch (direction)
	{
	case Block::Direction::Down:
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].y >= BlockManager::CellMatrixHeight - 1) ||
				(this->m_matrixCellState[(int)position.points[i].x][(int)position.points[i].y + 1] == CellState::Dead))
			{
				return false;
			}
		}
		break;

	case Block::Direction::Left:
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].x <= 0) ||
				(this->m_matrixCellState[(int)position.points[i].x - 1][(int)position.points[i].y] == CellState::Dead))
			{
				return false;
			}
		}
		break;

	case Block::Direction::Right:
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].x >= BlockManager::CellMatrixWidth - 1) ||
				(this->m_matrixCellState[(int)position.points[i].x + 1][(int)position.points[i].y] == CellState::Dead))
			{
				return false;
			}
		}
		break;

	case Block::Direction::Up:
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].y <= 0) ||
				(this->m_matrixCellState[(int)position.points[i].x][(int)position.points[i].y - 1] == CellState::Dead))
			{
				return false;
			}
		}

	default:
		break;
	}
	
	return true;
} //bool BlockManager::_currentBlockCanDrop()

void BlockManager::_currentBlockDoMove(Block::Direction direction)
{
	this->_updateCellMatrixBeforeMove(direction);
	this->m_blockDropping->doMove(direction);

	if (direction == Block::Direction::Down)
	{
		float y = this->m_blockDropping->getPositionY();
		this->m_blockDropping->setPositionY((int)y - Block::CellSize);
	}
	else if (direction == Block::Direction::Left)
	{
		float x = this->m_blockDropping->getPositionX();
		this->m_blockDropping->setPositionX((int)x - Block::CellSize);
	}
	else if (direction == Block::Direction::Right)
	{
		float x = this->m_blockDropping->getPositionX();
		this->m_blockDropping->setPositionX((int)x + Block::CellSize);
	}
	else
	{
		float y = this->m_blockDropping->getPositionY();
		this->m_blockDropping->setPositionY((int)y + Block::CellSize);
	}
} //void BlockManager::_currentBlockDoDrop()

void BlockManager::_currentBlockStopDrop()
{
	Block::CellPosition blockPrePosition = this->m_blockDropping->getCellPosition();

	this->_updateCellMatrixBeforeDie();

	this->_rePaintDeadBlocks();
	this->_eliminateLines();

	this->removeChild(m_blockDropping, false);

	if (m_blockDropping)
	{
		m_blockDropping->autorelease();
	}

	this->m_blockDropping = NULL;

	this->_pushNewBlock();

	Block::CellPosition blockCurrentPosition = this->m_blockDropping->getCellPosition();

	if (this->_blockOverlayed(blockPrePosition, blockCurrentPosition))
	{
		this->_endGame();
	}
}

bool BlockManager::_currentBlockCanTurn90Degrees()
{
	if (this->m_blockDropping->getBlockType() == Block::BlockType::O)
	{
		return false;
	}

	Block::CellPosition turnedPosition = this->m_blockDropping->doTurn90Degrees(false);

	for (int i = 0; i < 4; i++)
	{
		if (turnedPosition.points[i].x < 0 || 
			turnedPosition.points[i].y < 0 ||
			turnedPosition.points[i].x > BlockManager::CellMatrixWidth - 1 || 
			turnedPosition.points[i].y > BlockManager::CellMatrixHeight - 1 ||
			this->m_matrixCellState[(int)turnedPosition.points[i].x][(int)turnedPosition.points[i].y] == BlockManager::CellState::Dead)
		{
			return false;
		}
	}

	return true;

} //bool BlockManager::_currentBlockCanTurn90Degrees()

void BlockManager::_currentBlockDoTurn90Degrees()
{
 	Block::CellPosition originalPosition = this->m_blockDropping->getCellPosition();

	this->m_blockDropping->doTurn90Degrees(true);

	Block::CellPosition newPosition = this->m_blockDropping->getCellPosition();

	this->_updateCellMatrixAfterChanged(originalPosition, newPosition);

	this->m_blockDropping->getSprite()->setRotation(this->m_blockDropping->getDegree());
} //void BlockManager::_currentBlockDoTurn90Degrees()

/********************************************************/

void BlockManager::_updateCellMatrixBeforeMove(Block::Direction direction)
{
	Block::CellPosition position = this->m_blockDropping->getCellPosition();

	for (int i = 0; i < 4; i++)
	{
		this->m_matrixCellState[(int)position.points[i].x][(int)position.points[i].y] = BlockManager::CellState::Empty;

		if (direction == Block::Direction::Down)
		{
			this->m_matrixCellState[(int)position.points[i].x][(int)position.points[i].y + 1] = BlockManager::CellState::Dropping;
		}
		else if (direction == Block::Direction::Left)
		{
			this->m_matrixCellState[(int)position.points[i].x - 1][(int)position.points[i].y] = BlockManager::CellState::Dropping;
		}
		else if (direction == Block::Direction::Right)
		{
			this->m_matrixCellState[(int)position.points[i].x + 1][(int)position.points[i].y] = BlockManager::CellState::Dropping;
		}
		else
		{
			this->m_matrixCellState[(int)position.points[i].x][(int)position.points[i].y - 1] = BlockManager::CellState::Dropping;
		}
	}
	
} //void BlockManager::_updateCellMatrixForMove()

void BlockManager::_updateCellMatrixBeforeDie()
{
	Block::CellPosition position = this->m_blockDropping->getCellPosition();

	for (int i = 0; i < 4; i++)
	{
		this->m_matrixCellState[(int)position.points[i].x][(int)position.points[i].y] = BlockManager::CellState::Dead;
	}
} //void BlockManager::_updateCellMatrixForDie()

void BlockManager::_updateCellMatrixAfterChanged(Block::CellPosition originalPosition, Block::CellPosition newPosition)
{
	for (int i = 0; i < 4; i++)
	{
		this->m_matrixCellState[(int)originalPosition.points[i].x][(int)originalPosition.points[i].y] = CellState::Empty;
	}
	for (int i = 0; i < 4; i++)
	{
		this->m_matrixCellState[(int)newPosition.points[i].x][(int)newPosition.points[i].y] = CellState::Dropping;
	}
}

int BlockManager::_eliminateLines()
{
	int lineCounter = 0;
	int lineNums[Block::BlockWidthCount];

	for (int i = 0; i < BlockManager::CellMatrixHeight; i++)
	{
		if (this->_isLineFilled(i))
		{
			lineNums[lineCounter] = i;
			this->_eliminateSingleLine(i);
			lineCounter++;
		}
	}

	if (lineCounter > 0)
	{
		this->m_boundDisplayManager->lineEliminated(lineCounter, this);
		this->_rePaintDeadBlocks();
	}
	
	return lineCounter;
} //void BlockManager::_eliminateLines()

bool BlockManager::_blockOverlayed(Block::CellPosition p_block1, Block::CellPosition p_block2)
{
	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			if (p_block1.points[i1].x == p_block2.points[i2].x && p_block1.points[i1].y == p_block2.points[i2].y)
			{
				return true;
			}
		}
	}
	return false;
} //bool BlockManager::_blockOverlayed(Block::CellPosition p_block1, Block::CellPosition p_block2)

//Unfinished
void BlockManager::_endGame()
{
	this->unscheduleUpdate();
	CCLog("END");
} //void BlockManager::_endGame();

/********************************************************/

//Unfinished
void BlockManager::_eliminateSingleLine(int lineNum)
{
	for (int x = 0; x < BlockManager::CellMatrixWidth; x++)
	{
		for (int y = lineNum; y >= 0; y--)
		{
			if (y == 0)
			{
				this->m_matrixCellState[x][y] = BlockManager::CellState::Empty;
				this->m_matrixDeadBlockSprites[x][y] = NULL;
			}
			else
			{
				this->m_matrixCellState[x][y] = this->m_matrixCellState[x][y - 1];
				this->m_matrixDeadBlockSprites[x][y] = this->m_matrixDeadBlockSprites[x][y - 1];
			}
		}
	}
} //void BlockManager::_eliminateSingleLine(int lineNum)

//Unfinished
void BlockManager::_isTetris(int startLine)
{
	
} //void BlockManager::_isTetris(int startLine)

void BlockManager::_rePaintDeadBlocks()
{
	this->m_spriteBatchNodeDeadBlocks->removeAllChildren();

	for (int x = 0; x < BlockManager::CellMatrixWidth; x++)
	{
		for (int y = 0; y < BlockManager::CellMatrixHeight; y++)
		{
			if (this->m_matrixCellState[x][y] == CellState::Dead)
			{
				CCSprite* temp = CCSprite::createWithTexture(this->m_spriteBatchNodeDeadBlocks->getTexture());
				temp->setPosition(this->convertPositionToCenterPosition(convertBlockPositionToPixelPosition(ccp(x, y))));
				this->m_spriteBatchNodeDeadBlocks->addChild(temp);
				this->m_matrixDeadBlockSprites[x][y] = temp;
			}
		}
	}
} //void BlockManager::_rePaintDeadBlocks()

#pragma endregion