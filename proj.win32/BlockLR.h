#ifndef __BLOCK_L_R_H__
#define __BLOCK_L_R_H__

#include "cocos2d.h"
#include "Block.h"

class BlockLR :public Block
{
public:
	BlockLR();
	~BlockLR();
	CREATE_FUNC(BlockLR);
	virtual bool init();

public:
//	virtual bool doTurn90Degrees();
//	virtual bool doMove(Direction direction);

private:
//	virtual void _limitLine(Direction direction);
//	virtual bool _canMove(Direction direction);

}; //class BlockLR: public Block

#endif