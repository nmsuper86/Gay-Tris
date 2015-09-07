#include "BlockLR.h"
#include "BlockManager.h"

BlockLR::BlockLR()
{

} //BlockLR::BlockLR()

BlockLR::~BlockLR()
{

} //BlockLR::~BlockLR()

bool BlockLR::init()
{
	this->bindSprite(CCSprite::create("BlockLR.png"));
	this->setBlockData(ccp(2, 0), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 0));
	this->setBlockData(ccp(2, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 1));
	this->setBlockData(ccp(2, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 2));
	this->setBlockData(ccp(1, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 2));
	this->m_type = BlockType::L_Reverse;
	return true;
} //bool BlockLR::init()