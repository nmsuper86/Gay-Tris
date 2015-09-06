#ifndef __BLOCK_O_H__
#define __BLOCK_O_H__

#include "cocos2d.h"
#include "Block.h"

class BlockO :public Block
{
public:
	BlockO();
	~BlockO();
	CREATE_FUNC(BlockO);
	virtual bool init();

public:
	//	virtual bool doTurn90Degrees();
	//	virtual bool doMove(Direction direction);

private:
	//	virtual void _limitLine(Direction direction);
	//	virtual bool _canMove(Direction direction);

}; //class BlockO :public Block

#endif //__BLOCK_O_H__