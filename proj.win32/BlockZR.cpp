#include "BlockZR.h"
#include "BlockManager.h"

BlockZR::BlockZR()
{

} //BlockZR::BlockZR()

BlockZR::~BlockZR()
{

} //BlockZR::~BlockZR()

BlockZR* BlockZR::create(BlockManager* p_blockManagerToBind)
{
	BlockZR* pRet = new BlockZR();
	if (pRet && pRet->init(p_blockManagerToBind))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}


bool BlockZR::init(BlockManager* p_blockManagerToBind)
{
	this->bindSprite(CCSprite::create("BlockZR.png"));
	this->setBlockData(ccp(2, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 1));
	this->setBlockData(ccp(3, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 3, 1));
	this->setBlockData(ccp(1, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 2));
	this->setBlockData(ccp(2, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 2));
	this->m_type = BlockType::Z_Reverse;

	this->m_manager = p_blockManagerToBind;
	return true;
} //bool BlockZR::init()