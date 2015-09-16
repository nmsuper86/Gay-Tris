#ifndef __BLOCK_T_H__
#define __BLOCK_T_H__

#include "cocos2d.h"
#include "Block.h"

class BlockT :public Block
{
public:
	BlockT();
	~BlockT();
	static BlockT* create(BlockManager* p_blockManagerToBind);
	virtual bool init(BlockManager* p_blockManagerToBind);

}; //class BlockT: public Block

#endif //__BLOCK_T_H__