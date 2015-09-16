#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class BlockManager;

class BlockI;

class Block:public Entity
{
public:
	typedef enum
	{
		Up,
		Down,
		Left,
		Right
	}Direction;
	typedef enum
	{
		I,
		L,
		L_Reverse,
		T,
		Z,
		Z_Reverse,
		O
	}BlockType;
	typedef struct
	{
		CCPoint points[4];
	}CellPosition;

	static const int CellSize = 25;
	static const int BlockWidthCount = 4;

protected:
	CCPoint m_blockData[Block::BlockWidthCount][Block::BlockWidthCount];
	BlockManager* m_manager;
	BlockType m_type;
	int m_timeCounter;
	int m_degree;

public: //System functions
	Block();
	~Block();
	static Block* create(BlockManager* p_blockManagerToBind);
	virtual bool init(BlockManager* p_blockManagerToBind);

public: //Custom functions
	virtual CellPosition doTurn90Degrees(bool saveState); //旋转方块并返回旋转后的位置信息 saveState代表是否保存旋转后的结果
	virtual bool doMove(Direction direction);
	void bindManager(BlockManager* manager);
	bool increaseTimeCounter(int updateTime); //时间自增后返回是否需要更新位置
	static Block* generateNewBlock(BlockManager* blockManagerToBind);
	CellPosition getCellPosition();
	void resetTimeCounter(); //重置计数器
	void initializeBlock(); //初始化方块内的数据
	void setBlockData(CCPoint blockPoint, CCPoint stagePoint); //子类通过此函数设定blockData矩阵中的坐标值
	BlockType getBlockType();
	int getDegree();
	
}; //class Block

#endif //__BLOCK_H__