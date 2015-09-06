#ifndef __BLOCK_T_H__
#define __BLOCK_T_H__

#include "cocos2d.h"
#include "Block.h"

class BlockT :public Block
{
public:
	BlockT();
	~BlockT();
	CREATE_FUNC(BlockT);
	virtual bool init();

public:
	//	virtual bool doTurn90Degrees();
	//	virtual bool doMove(Direction direction);

private:
	//	virtual void _limitLine(Direction direction);
	//	virtual bool _canMove(Direction direction);

}; //class BlockT: public Block

#endif //__BLOCK_T_H__