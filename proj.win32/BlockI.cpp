#include "BlockI.h"
#include "BlockManager.h"

BlockI::BlockI()
{
	
} //BlockI::BlockI()

BlockI::~BlockI()
{

} //BlockI::~BlockI()

bool BlockI::init()
{
	this->bindSprite(CCSprite::create("BlockI.png"));
	for (int i = 0; i < 4; i++)
	{
		this->setBlockData(ccp(2, i), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + i, 2));
	}
	return true;
} //bool BlockI::init()