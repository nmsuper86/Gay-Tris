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
	this->bindSprite(CCSprite::create("Images\BlockI.png"));
	for (int i = 0; i < 4; i++)
	{
		this->setBlockData(ccp(1, i), ccp(1, CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + i));
	}
} //bool BlockI::init()