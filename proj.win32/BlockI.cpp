#include "BlockI.h"
#include "BlockManager.h"

BlockI::BlockI()
{
	
} //BlockI::BlockI()

BlockI::~BlockI()
{

} //BlockI::~BlockI()

BlockI* BlockI::create(BlockManager* p_blockManagerToBind)
{
	BlockI* pRet = new BlockI();
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

bool BlockI::init(BlockManager* p_blockManagerToBind)
{
	this->bindSprite(CCSprite::create("BlockI.png"));
	for (int i = 0; i < 4; i++)
	{
		this->setBlockData(ccp(i, 1), ccp(BlockManager::CellMatrixWidth / 2 - Block::BlockWidthCount / 2 + i, 1));
	}
	this->m_type = BlockType::I;
	this->m_manager = p_blockManagerToBind;
	return true;
} //bool BlockI::init()