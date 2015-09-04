#ifndef __BLOCK_L_H__
#define __BLOCK_L_H__

#include "cocos2d.h"
#include "Block.h"

using namespace cocos2d;

class BlockL:public Block
{
public:
	BlockL();
	~BlockL();
	CREATE_FUNC(BlockL);
	virtual bool init();

public:
//	virtual bool doTurn90Degrees();
//	virtual bool doMove(Direction direction);

private:
//	virtual void _limitLine(Direction direction);
//	virtual bool _canMove(Direction direction);


}; //class BlockL:public Block

#endif // !__BLOCK_L_H__




