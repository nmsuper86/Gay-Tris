#include "BlockZR.h"
#include "BlockManager.h"

BlockZR::BlockZR()
{

} //BlockZR::BlockZR()

BlockZR::~BlockZR()
{

} //BlockZR::~BlockZR()

bool BlockZR::init()
{
	this->bindSprite(CCSprite::create("BlockZR.png"));
	this->setBlockData(ccp(2, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 1));
	this->setBlockData(ccp(3, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 3, 1));
	this->setBlockData(ccp(1, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 2));
	this->setBlockData(ccp(2, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 2));
	this->m_type = BlockType::Z_Reverse;
	return true;
} //bool BlockZR::init()