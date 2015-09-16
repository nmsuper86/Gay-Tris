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
	static BlockI* create(BlockManager* p_blockManagerToBind);
	virtual bool init(BlockManager* p_blockManagerToBind);
}; //class BlockI

#endif //!__BLOCK_I_H__