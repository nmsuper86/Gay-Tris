#include "BlockL.h"
#include "BlockManager.h"

BlockL::BlockL()
{

} //BlockL::BlockL()

BlockL::~BlockL()
{

} //BlockL::~BlockL()

BlockL* BlockL::create(BlockManager* p_blockManagerToBind)
{
	BlockL* pRet = new BlockL();
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

bool BlockL::init(BlockManager* p_blockManagerToBind)
{
	this->bindSprite(CCSprite::create("BlockL.png"));
	this->setBlockData(ccp(1, 0), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 0));
	this->setBlockData(ccp(1, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 1));
	this->setBlockData(ccp(1, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 2));
	this->setBlockData(ccp(2, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 2));
	this->m_type = BlockType::L;
	this->m_manager = p_blockManagerToBind;

	return true;
}