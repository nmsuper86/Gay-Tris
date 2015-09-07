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
	this->m_degree = 0;
//	this->m_position = ccp(CELL_MATRIX_WIDTH / 2, 2);
} //Block::Block()

Block::~Block()
{

} //Block::~Block()

bool Block::init()
{
	return true;
} //bool Block::init()

Block::CellPosition Block::doTurn90Degrees(bool saveState)
{
	CellPosition position; //位置合法则返回位置 非法则把所有位置变为（-1， -1）
	int positionPointer = 0;

	CCPoint point00; //block左上角的方块坐标
#pragma region 获取左上角的block
	for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
	{
		for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
		{
			if (this->m_blockData[x][y].x != -1)
			{
				point00.x = m_blockData[x][y].x - x;
				point00.y = m_blockData[x][y].y - y;
				break;
			}
		}
	}
#pragma endregion

	CCPoint tempCellMatrix[BLOCK_WIDTH_COUNT][BLOCK_WIDTH_COUNT];
#pragma region 旋转blockData矩阵
	if (this->m_type == BlockType::I && this->m_degree == 90)
	{
		for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
		{
			for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
			{
				tempCellMatrix[y][BLOCK_WIDTH_COUNT - x - 1] = this->m_blockData[x][y];
			}
		}
	}
	else
	{
		for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
		{
			for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
			{
				tempCellMatrix[BLOCK_WIDTH_COUNT - y - 1][x] = this->m_blockData[x][y];
			}
		}
	}
#pragma endregion

#pragma region 修改矩阵中的数据并保存CellPosition位置 
	for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
	{
		for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
		{
			if (tempCellMatrix[x][y].x != -1)
			{
				tempCellMatrix[x][y].x = position.points[positionPointer].x = point00.x + x;
				tempCellMatrix[x][y].y = position.points[positionPointer].y = point00.y + y;
				positionPointer++;
			}
		}
	}
#pragma endregion

	if (saveState)
	{
		if (this->m_type == BlockType::I && this->m_degree == 90)
		{
			this->m_degree = 0;
		}
		else
		{
			this->m_degree = (this->m_degree + 90) % 360;
		}

		for (int x = 0; x < BLOCK_WIDTH_COUNT; x++)
		{
			for (int y = 0; y < BLOCK_WIDTH_COUNT; y++)
			{
				this->m_blockData[x][y] = tempCellMatrix[x][y];
			}
		}
	}

	return position;
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

Block::BlockType Block::getBlockType()
{
	return this->m_type;
}

int Block::getDegree()
{
	return this->m_degree;
}


