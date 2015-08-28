#include "BlockManager.h"


#pragma region 系统调用

BlockManager::BlockManager()
{
	
} //BlockManager::BlockManager()

BlockManager::~BlockManager()
{

} //BlockManager::~BlockManager()

bool BlockManager::init()
{
	//初始化单元状态矩阵
	for (int x = 0; x < CELL_MATRIX_WIDTH; x++)
	{
		for (int y = 0; y < CELL_MATRIX_HEIGHT; y++)
		{
			this->m_cellMatrix[x][y] = BlockManager::CellState::Empty;
		}
	}

	//设定默认更新频率
	this->m_updateTime = DEFAULT_REFRESH_TIME;

	//创建第一个块
	this->m_nextBlock = _createNewBlock();
	this->m_nextBlock->bindManager(this);
	this->m_nextBlock->retain();

	//放入第一个块并创建第二个块
	this->_pushNewBlock();

	//初始化已死方块批量精灵
	this->m_deadBlockBatch = CCSpriteBatchNode::create("BlockDead.png", CELL_MATRIX_WIDTH * CELL_MATRIX_HEIGHT);
	this->addChild(this->m_deadBlockBatch);
/**********************************************/
//	this->scheduleUpdate();
//	this->_rePaintDeadBlocks();
/**********************************************/

	return true;
}

void BlockManager::update(float delta)
{
//	CCLog(CCStringMake("UF%d", this)->getCString());
	if (!this->_shouldBlockTryDrop())
	{
		this->_donotTryDrop();
	}
	else
	{
		this->_doTryDrop();
	}
//	CCLog(CCStringMake("UR%d", this)->getCString());
} //void BlockManager::update(float delta)

#pragma endregion

#pragma region 公有自定义函数

int BlockManager::getUpdateTime()
{
	return m_updateTime;
//	return 30;
}

void BlockManager::bindDisplayManager(DisplayManger* manager)
{
	this->m_displayManager = manager;
} //void BlockManager::bindDisplayManager(DisplayManager* manager)

CCPoint BlockManager::convertBlockToPixel(CCPoint blockPoint)
{
	CCPoint resultPoint;
	resultPoint.x = this->getPositionX() - CELL_MATRIX_WIDTH / 2 * CELL_SIZE + blockPoint.x * CELL_SIZE;
	resultPoint.y = this->getPositionY() + CELL_MATRIX_HEIGHT / 2 * CELL_SIZE - blockPoint.y * CELL_SIZE;
	return resultPoint;
} //CCPoint BlockManager::convertBlockToPixel(CCPoint blockPoint)

#pragma endregion

#pragma region 私有自定义函数

Block* BlockManager::_createNewBlock()
{
	return Block::generateNewBlock();
}

/*******************************************************/

bool BlockManager::_shouldBlockTryDrop()
{
//	CCLog(CCStringMake("SF%d %d", this, this->m_currentBlock)->getCString());
	return this->m_currentBlock->increaseTimeCounter();
//	CCLog(CCStringMake("SF%d %d", this, this->m_currentBlock)->getCString());
}

void BlockManager::_donotTryDrop()
{
	//Nothing
} //void BlockManager::_donotTryDrop()

void BlockManager::_doTryDrop()
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

/********************************************************/

bool BlockManager::_currentBlockCanMove(Block::Direction direction)
{
	Block::CellPosition position = this->m_currentBlock->getCellPosition();

	if (direction == Block::Direction::Down)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].y >= CELL_MATRIX_HEIGHT - 1) ||
				(this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y + 1] == CellState::Dead))
			{
				return false;
			}
		}

	}
	else if (direction == Block::Direction::Left)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].x <= 0) ||
				(this->m_cellMatrix[(int)position.points[i].x - 1][(int)position.points[i].y] == CellState::Dead))
			{
				return false;
			}
		}
	}
	else if (direction == Block::Direction::Right)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].x >= CELL_MATRIX_WIDTH - 1) ||
				(this->m_cellMatrix[(int)position.points[i].x + 1][(int)position.points[i].y] == CellState::Dead))
			{
				return false;
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if ((position.points[i].y <= 0) ||
				(this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y - 1] == CellState::Dead))
			{
				return false;
			}
		}
	}
	
	return true;
} //bool BlockManager::_currentBlockCanDrop()

void BlockManager::_currentBlockDoMove(Block::Direction direction)
{
	this->_updateCellMatrixForMove(direction);
	this->m_currentBlock->doMove(direction);
	this->m_currentBlock->setPosition(
		ccp(this->m_currentBlock->getPositionX(),
		    this->m_currentBlock->getPositionY() - CELL_SIZE
		));
} //void BlockManager::_currentBlockDoDrop()

void BlockManager::_currentBlockStopDrop()
{
	this->_updateCellMatrixForDie();

	this->_rePaintDeadBlocks();
//	this->_eliminateLines();
	m_currentBlock->retain();
	this->removeChild(m_currentBlock, false);
//	this->m_currentBlock->release();
	this->m_currentBlock = NULL;

	this->_pushNewBlock();

// 	if (!this->_canGameContinue())
// 	{
// 		this->_endGame();
// 	}
}

/********************************************************/

void BlockManager::_updateCellMatrixForMove(Block::Direction direction)
{
	Block::CellPosition position = this->m_currentBlock->getCellPosition();

	for (int i = 0; i < 4; i++)
	{
		this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y] = BlockManager::CellState::Empty;

		if (direction == Block::Direction::Down)
		{
			this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y + 1] = BlockManager::CellState::Dropping;
		}
		else if (direction == Block::Direction::Left)
		{
			this->m_cellMatrix[(int)position.points[i].x - 1][(int)position.points[i].y] = BlockManager::CellState::Dropping;
		}
		else if (direction == Block::Direction::Right)
		{
			this->m_cellMatrix[(int)position.points[i].x + 1][(int)position.points[i].y] = BlockManager::CellState::Dropping;
		}
		else
		{
			this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y - 1] = BlockManager::CellState::Dropping;
		}
	}
	
} //void BlockManager::_updateCellMatrixForMove()

void BlockManager::_updateCellMatrixForDie()
{
	Block::CellPosition position = this->m_currentBlock->getCellPosition();

	for (int i = 0; i < 4; i++)
	{
		this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y] = BlockManager::CellState::Dead;
	}
} //void BlockManager::_updateCellMatrixForDie()

int BlockManager::_eliminateLines()
{
	int lineCounter = 0;
	int lineNums[4];
	for (int i = CELL_MATRIX_HEIGHT - 1; i >= 0; i--)
	{
		if (this->_isLineFilled(i))
		{
			lineNums[lineCounter] = i;
			lineCounter++;
			this->_eliminateSingleLine(i);
			this->m_displayManager->lineEliminated();
		}
	}

	if (lineCounter > 1)
	{
		if (lineCounter == 4)
		{
			this->_isTetris(lineNums[3]);
		}
		else
		{
			int startLineNum = (lineNums[0] + lineNums[lineCounter - 1]) / 2;
			this->_eliminateMultiLine(startLineNum);
		}
	}

	if (lineCounter > 0)
	{
		this->_rePaintDeadBlocks();
	}
	
	return lineCounter;
} //void BlockManager::_eliminateLines()

void BlockManager::_pushNewBlock()
{
	this->m_currentBlock = this->m_nextBlock;
	this->m_currentBlock->setPosition(this->convertBlockToPixel(ccp(CELL_MATRIX_WIDTH / 2, BLOCK_WIDTH_COUNT / 2)));

	Block::CellPosition position = this->m_currentBlock->getCellPosition();
	for (int i = 0; i < 4; i++)
	{
		this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y] = BlockManager::CellState::Dropping;
	}
	this->addChild(this->m_currentBlock);

	this->m_nextBlock = Block::generateNewBlock();
	this->m_nextBlock->bindManager(this);
	this->m_nextBlock->retain();
//	this->m_displayManager->nextBlockChanged(this->m_nextBlock);
} //void BlockManager::_pushNewBlock()

bool BlockManager::_canGameContinue()
{
	Block::CellPosition position = this->m_currentBlock->getCellPosition();
	for (int i = 0; i < 4; i++)
	{
		if (this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y] == BlockManager::CellState::Dead)
		{
			return false;
		}
	}
	return true;

} //bool BlockManager::_canGameContinue()

//Unfinished
void BlockManager::_endGame()
{
	this->unscheduleUpdate();
} //void BlockManager::_endGame();

/********************************************************/

//Unfinished
void BlockManager::_eliminateSingleLine(int lineNum)
{

} //void BlockManager::_eliminateSingleLine(int lineNum)

//Unfinished
void BlockManager::_eliminateMultiLine(int startLine)
{

} //void BlockManager::_eliminateMultiLine(int startLine)

//Unfinished
void BlockManager::_isTetris(int startLine)
{

} //void BlockManager::_isTetris(int startLine)

void BlockManager::_rePaintDeadBlocks()
{
	this->m_deadBlockBatch->setPosition(ccp(0, 0));
	this->m_deadBlockBatch->removeAllChildren();

	for (int x = 0; x < CELL_MATRIX_WIDTH; x++)
	{
		for (int y = 0; y < CELL_MATRIX_HEIGHT; y++)
		{
			if (this->m_cellMatrix[x][y] == CellState::Dead)
			{
				CCSprite* temp = CCSprite::createWithTexture(this->m_deadBlockBatch->getTexture());
				temp->setPosition(this->convertRBToCenter(convertBlockToPixel(ccp(x, y))));
				this->m_deadBlockBatch->addChild(temp);
			}
		}
	}
} //void BlockManager::_rePaintDeadBlocks()


#pragma endregion