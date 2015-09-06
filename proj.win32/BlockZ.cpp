#include "BlockZ.h"
#include "BlockManager.h"

BlockZ::BlockZ()
{

} //BlockZ::BlockZ()

BlockZ::~BlockZ()
{

} //BlockZ::~BlockZ()

bool BlockZ::init()
{
	this->bindSprite(CCSprite::create("BlockZ.png"));
	this->setBlockData(ccp(0, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 0, 1));
	this->setBlockData(ccp(1, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 1));
	this->setBlockData(ccp(1, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 2));
	this->setBlockData(ccp(2, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 2));
	return true;
} //bool BlockZ::init()
