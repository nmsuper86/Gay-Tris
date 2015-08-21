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
	this->scheduleUpdate();

	for (int x = 0; x < CELL_MATRIX_WIDTH; x++)
	{
		for (int y = 0; y < CELL_MATRIX_HEIGHT; y++)
		{
			this->m_cellMatrix[x][y] = BlockManager::CellState::Empty;
		}
	}

	this->m_updateTime = DEFAULT_REFRESH_TIME;

	this->m_nextBlock = _createNewBlock();
	this->m_nextBlock->bindManager(this);

	this->_pushNewBlock();

	return true;
}

void BlockManager::update(float delta)
{
	if (this->_shouldBlockTryDrop())
	{
		this->_donotTryDrop();
	}
	else
	{
		this->_doTryDrop();
	}
} //void BlockManager::update(float delta)

#pragma endregion

#pragma region 公有自定义函数

int BlockManager::getUpdateTime()
{
	return this->m_updateTime;
}

void BlockManager::bindDisplayManager(DisplayManger* manager)
{
	this->m_displayManager = manager;
} //void BlockManager::bindDisplayManager(DisplayManager* manager)

CCPoint BlockManager::convertBlockToPixel(CCPoint blockPoint)
{
	return ccp(blockPoint.x * CELL_SIZE, blockPoint.y * CELL_SIZE);
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
	return this->m_currentBlock->increaseTimeCounter();
}

void BlockManager::_donotTryDrop()
{
	//Nothing
} //void BlockManager::_donotTryDrop()

void BlockManager::_doTryDrop()
{
	if (this->_currentBlockCanMove(Block::Direction::Down))
	{
		this->_currentBlockDoDrop();
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

void BlockManager::_currentBlockDoDrop()
{
	this->m_currentBlock->doMove(Block::Direction::Down);
	this->_updateCellMatrixForMove(Block::Direction::Down);
//	this->m_currentBlock->resetTimeCounter();
} //void BlockManager::_currentBlockDoDrop()

void BlockManager::_currentBlockStopDrop()
{
	this->_updateCellMatrixForDie();

	this->removeChild(m_currentBlock);

	this->_eliminateLines();

	this->_pushNewBlock();

	if (!this->_canGameContinue())
	{
		this->_endGame();
	}
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

	this->_rePaintDeadBlocks();
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
	this->addChild(this->m_currentBlock);
	this->m_currentBlock->getSprite()->setPosition(this->convertBlockToPixel(ccp(CELL_MATRIX_WIDTH / 2, BLOCK_WIDTH_COUNT / 2)));

	Block::CellPosition position = this->m_currentBlock->getCellPosition();
	for (int i = 0; i < 4; i++)
	{
		this->m_cellMatrix[(int)position.points[i].x][(int)position.points[i].y] = BlockManager::CellState::Dropping;
	}

	this->m_nextBlock = Block::generateNewBlock();
	this->m_displayManager->nextBlockChanged(this->m_nextBlock);
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
		return true;
	}

} //bool BlockManager::_canGameContinue()

void BlockManager::_endGame()
{
	this->unscheduleUpdate();
} //void BlockManager::_endGame();

/********************************************************/



#pragma endregion