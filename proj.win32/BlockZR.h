#ifndef __BLOCK_Z_R_H__
#define __BLOCK_Z_R_H__

#include "cocos2d.h"
#include "Block.h"

class BlockZR :public Block
{
public:
	BlockZR();
	~BlockZR();
	CREATE_FUNC(BlockZR);
	virtual bool init();

public:
	//	virtual bool doTurn90Degrees();
	//	virtual bool doMove(Direction direction);

private:
	//	virtual void _limitLine(Direction direction);
	//	virtual bool _canMove(Direction direction);

}; //class BlockZR: public Block

#endif //__BLOCK_Z_R_H__