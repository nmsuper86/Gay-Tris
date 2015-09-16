#ifndef __BLOCK_Z_H__
#define __BLOCK_Z_H__

#include "cocos2d.h"
#include "Block.h"

class BlockZ :public Block
{
public:
	BlockZ();
	~BlockZ();
	static BlockZ* create(BlockManager* p_blockManagerToBind);
	virtual bool init(BlockManager* p_blockManagerToBind);

}; //class BlockZ: public Block

#endif //__BLOCK_Z_H__