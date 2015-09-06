#include "Block.h"
#include "BlockManager.h"
#include "BlockI.h"
#include "BlockL.h"
#include "BlockLR.h"
#include "BlockO.h"
#include "BlockT.h"
#include "BlockZ.h"
#include "BlockZR.h"

Block::Block()
{
	for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
	{
		for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
		{
			this->m_blockData[x][y] = ccp(-1, -1);
		}
	}

	this->m_timeCounter = 0;
	this->m_position = ccp(CELL_MATRIX_WIDTH / 2, 2);
} //Block::Block()

Block::~Block()
{

} //Block::~Block()

bool Block::init()
{
	return true;
} //bool Block::init()

bool Block::doTurn90Degrees()
{
	return false;
} //bool Block::doTurn90Degrees()

bool Block::doMove(Direction direction)
{
	if (direction == Direction::Down)
	{
		for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
		{
			for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
			{
				if (this->m_blockData[x][y].x != -1)
				{
					this->m_blockData[x][y].y++;
				}
			}
		}
		
	}
	else if (direction == Direction::Left)
	{
		for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
		{
			for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
			{
				if (this->m_blockData[x][y].x != -1)
				{
					this->m_blockData[x][y].x--;
				}
			}
		}
	}
	else if (direction == Direction::Right)
	{
		for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
		{
			for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
			{
				if (this->m_blockData[x][y].x != -1)
				{
					this->m_blockData[x][y].x++;
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
		{
			for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
			{
				if (this->m_blockData[x][y].x != -1)
				{
					this->m_blockData[x][y].y--;
				}
			}
		}
	}
	return true;
} //bool Block::doMove(Direction direction)

void Block::bindManager(BlockManager* manager)
{
	this->m_manager = manager;
} //void Block::bindManager(BlockManager* manager)

bool Block::increaseTimeCounter(int updateTime)
{
	this->m_timeCounter++;
	if (this->m_timeCounter >= updateTime)
	{
		this->m_timeCounter = 0;
		return true;
	}
	else
	{
		return false;
	}
}// bool Block::increaseTimeCounter()

Block* Block::generateNewBlock()
{
	Block* block = NULL;

	int blockType = CCRANDOM_0_1() * 7;

	switch (blockType)
	{
	case 0:
		block = BlockI::create();
		break;

	case 1:
		block = BlockL::create();
		break;

	case 2:
		block = BlockLR::create();
		break;

	case 3:
		block = BlockO::create();
		break;

	case 4:
		block = BlockT::create();
		break;

	case 5:
		block = BlockZ::create();
		break;

	case 6:
		block = BlockZR::create();
		break;

	default:
		break;
	}

	return block;
}

Block::CellPosition Block::getCellPosition()
{
	CellPosition position;
	int counter = 0;
	for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
	{
		for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
		{
			if (this->m_blockData[x][y].x != -1)
			{
				position.points[counter++] = this->m_blockData[x][y];
			}
		}
	}
	return position;
} //CellPosition Block::getCellPosition()

void Block::setBlockData(CCPoint blockPoint, CCPoint stagePoint)
{
	this->m_blockData[(int)blockPoint.x][(int)blockPoint.y] = stagePoint;
} //void Block::setBlockData(CCPoint blockPoint, CCPoint stagePoint)


