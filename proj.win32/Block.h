#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Entity.h"

#define CELL_SIZE 25
#define BLOCK_WIDTH_COUNT 4

using namespace cocos2d;

class BlockManager;

class BlockI;

class Block:public Entity
{
public: //System functions
	Block();
	~Block();
	CREATE_FUNC(Block);
	virtual bool init();

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

public: //Custom functions
	virtual CellPosition doTurn90Degrees(bool saveState); //旋转方块并返回旋转后的位置信息 saveState代表是否保存旋转后的结果
	virtual bool doMove(Direction direction);
	void bindManager(BlockManager* manager);
//	void setIndexInArray(int index);
	bool increaseTimeCounter(int updateTime); //时间自增后返回是否需要更新位置
	static Block* generateNewBlock();
	CellPosition getCellPosition();
	void resetTimeCounter(); //重置计数器
	void initializeBlock(); //初始化方块内的数据
	void setBlockData(CCPoint blockPoint, CCPoint stagePoint); //子类通过此函数设定blockData矩阵中的坐标值
	BlockType getBlockType();
	int getDegree();
	

private:
//	virtual void _limitLine(Direction direction);
//	virtual bool _canMove(Direction direction);

protected:
	CCPoint m_blockData[BLOCK_WIDTH_COUNT][BLOCK_WIDTH_COUNT];
	BlockManager* m_manager;
	BlockType m_type;
	int m_timeCounter;
//	CCPoint m_position; //以精灵中心为基准 在管理器中 对应方块右下角的位置
	int m_degree;
//	int m_indexInArray;

}; //class Block

#endif //__BLOCK_H__