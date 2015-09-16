#include "BlockT.h"
#include "BlockManager.h"

BlockT::BlockT()
{

} //BlockT::BlockT()

BlockT::~BlockT()
{

} //BlockT::~BlockT()

BlockT* BlockT::create(BlockManager* p_blockManagerToBind)
{
	BlockT* pRet = new BlockT();
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

bool BlockT::init(BlockManager* p_blockManagerToBind)
{
	this->bindSprite(CCSprite::create("BlockT.png"));
	this->setBlockData(ccp(2, 0), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 0));
	this->setBlockData(ccp(1, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 1));
	this->setBlockData(ccp(2, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 1));
	this->setBlockData(ccp(2, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 2));
	this->m_type = BlockType::T;

	this->m_manager = p_blockManagerToBind;
	return true;
} //bool BlockT::init()