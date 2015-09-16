#ifndef __BLOCK_L_R_H__
#define __BLOCK_L_R_H__

#include "cocos2d.h"
#include "Block.h"

class BlockLR :public Block
{
public:
	BlockLR();
	~BlockLR();
	static BlockLR* create(BlockManager* p_blockManagerToBind);
	virtual bool init(BlockManager* p_blockManagerToBind);

}; //class BlockLR: public Block

#endif //__BLOCK_L_R_H__