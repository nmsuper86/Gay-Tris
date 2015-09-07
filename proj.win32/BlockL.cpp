#include "BlockL.h"
#include "BlockManager.h"

BlockL::BlockL()
{

} //BlockL::BlockL()

BlockL::~BlockL()
{

} //BlockL::~BlockL()

bool BlockL::init()
{
	this->bindSprite(CCSprite::create("BlockL.png"));
	this->setBlockData(ccp(1, 0), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 0));
	this->setBlockData(ccp(1, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 1));
	this->setBlockData(ccp(1, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 2));
	this->setBlockData(ccp(2, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 2));
	this->m_type = BlockType::L;
	return true;
}