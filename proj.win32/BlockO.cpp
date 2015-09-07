#include "BlockO.h"
#include "BlockManager.h"

BlockO::BlockO()
{

} //BlockO::BlockO()

BlockO::~BlockO()
{

} //BlockO::~BlockO()

bool BlockO::init()
{
	this->bindSprite(CCSprite::create("BlockO.png"));
	this->setBlockData(ccp(1, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 1));
	this->setBlockData(ccp(1, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 1, 2));
	this->setBlockData(ccp(2, 1), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 1));
	this->setBlockData(ccp(2, 2), ccp(CELL_MATRIX_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 + 2, 2));
	this->m_type = BlockType::O;
	return true;
} //bool BlockO::init()