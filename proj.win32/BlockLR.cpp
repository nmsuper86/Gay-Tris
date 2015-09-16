#include "BlockLR.h"
#include "BlockManager.h"

BlockLR::BlockLR()
{

} //BlockLR::BlockLR()

BlockLR::~BlockLR()
{

} //BlockLR::~BlockLR()

BlockLR* BlockLR::create(BlockManager* p_blockManagerToBind)
{
	BlockLR* pRet = new BlockLR();
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

bool BlockLR::init(BlockManager* p_blockManagerToBind)
{
	this->bindSprite(CCSprite::create("BlockLR.png"));
	this->setBlockData(ccp(2, 0), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 0));
	this->setBlockData(ccp(2, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 1));
	this->setBlockData(ccp(2, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 2));
	this->setBlockData(ccp(1, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 2));
	this->m_type = BlockType::L_Reverse;

	this->m_manager = p_blockManagerToBind;
	return true;
} //bool BlockLR::init()