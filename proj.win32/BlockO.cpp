#include "BlockO.h"
#include "BlockManager.h"

BlockO::BlockO()
{

} //BlockO::BlockO()

BlockO::~BlockO()
{

} //BlockO::~BlockO()

BlockO* BlockO::create(BlockManager* p_blockManagerToBind)
{
	BlockO* pRet = new BlockO();
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

bool BlockO::init(BlockManager* p_blockManagerToBind)
{
	this->bindSprite(CCSprite::create("BlockO.png"));
	this->setBlockData(ccp(1, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 1));
	this->setBlockData(ccp(1, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 1, 2));
	this->setBlockData(ccp(2, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 1));
	this->setBlockData(ccp(2, 2), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + 2, 2));
	this->m_type = BlockType::O;

	this->m_manager = p_blockManagerToBind;
	return true;
} //bool BlockO::init()