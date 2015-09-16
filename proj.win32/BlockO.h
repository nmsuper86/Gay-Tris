#ifndef __BLOCK_O_H__
#define __BLOCK_O_H__

#include "cocos2d.h"
#include "Block.h"

class BlockO :public Block
{
public:
	BlockO();
	~BlockO();
	static BlockO* create(BlockManager* p_blockManagerToBind);
	virtual bool init(BlockManager* p_blockManagerToBind);

}; //class BlockO :public Block

#endif //__BLOCK_O_H__