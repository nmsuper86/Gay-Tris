#include "BlockZ.h"
#include "BlockManager.h"

BlockZ::BlockZ()
{

} //BlockZ::BlockZ()

BlockZ::~BlockZ()
{

} //BlockZ::~BlockZ()

BlockZ* BlockZ::create(BlockManager* p_blockManagerToBind)
{
	BlockZ* pRet = new BlockZ();
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


bool BlockZ::init(BlockManager* p_blockManagerToBind)
{
	this->bindSprite(CCSprite::create("BlockZ.png"));
	this->setBlockData(ccp(0, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 0, 1));
	this->setBlockData(ccp(1, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 1));
	this->setBlockData(ccp(1, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 2));
	this->setBlockData(ccp(2, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 2));
	this->m_type = BlockType::Z;

	this->m_manager = p_blockManagerToBind;
	return true;
} //bool BlockZ::init()
