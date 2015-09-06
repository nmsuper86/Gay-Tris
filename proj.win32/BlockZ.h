#ifndef __BLOCK_Z_H__
#define __BLOCK_Z_H__

#include "cocos2d.h"
#include "Block.h"

class BlockZ :public Block
{
public:
	BlockZ();
	~BlockZ();
	CREATE_FUNC(BlockZ);
	virtual bool init();

public:
	//	virtual bool doTurn90Degrees();
	//	virtual bool doMove(Direction direction);

private:
	//	virtual void _limitLine(Direction direction);
	//	virtual bool _canMove(Direction direction);

}; //class BlockZ: public Block

#endif //__BLOCK_Z_H__