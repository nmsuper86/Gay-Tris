#ifndef __BLOCK_I_H__
#define __BLOCK_I_H__

#include "cocos2d.h"
#include "Block.h"

using namespace cocos2d;

class BlockI:public Block
{
public:
	BlockI();
	~BlockI();
	CREATE_FUNC(BlockI);
	virtual bool init();

public:
	virtual bool tryTurn90Degrees();
	virtual bool tryMove(Direction direction);

private:
	virtual void _limitLine(Direction direction);
	virtual bool _canMove(Direction direction);

}; //class BlockI

#endif //!__BLOCK_I_H__