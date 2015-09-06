#include "BlockT.h"
#include "BlockManager.h"

BlockT::BlockT()
{

} //BlockT::BlockT()

BlockT::~BlockT()
{

} //BlockT::~BlockT()

bool BlockT::init()
{
	this->bindSprite(CCSprite::create("BlockT.png"));
	this->setBlockData(ccp(2, 0), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 0));
	this->setBlockData(ccp(1, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 1));
	this->setBlockData(ccp(2, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 1));
	this->setBlockData(ccp(2, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 2));
	return true;
} //bool BlockT::init()