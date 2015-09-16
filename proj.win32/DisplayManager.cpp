#include "DisplayManager.h"
#include "BlockManager.h"

DisplayManger::DisplayManger()
{
	this->m_currentLevel = 1;
	this->m_totalScore = 0;
	this->m_linesInCurrentLevel = 0;
} //DisplayManager::DisplayManager()

DisplayManger::~DisplayManger()
{

} //DisplayManager::~DisplayManager()

bool DisplayManger::init()
{
	CCLabelTTF* labelNxt = CCLabelTTF::create("Next:", "Corbel", 25.0f);
	labelNxt->setPosition(ccp(-80, 270));
	this->addChild(labelNxt);

	CCLabelTTF* labelScr = CCLabelTTF::create("Score:", "Corbel", 25.0f);
	labelScr->setPosition(ccp(-80, 100));
	this->addChild(labelScr);

	CCLabelTTF* labelLvl = CCLabelTTF::create("Level:", "Corbel", 25.0f);
	labelLvl->setPosition(ccp(-80, 0));
	this->addChild(labelLvl);

	this->m_labelScore = CCLabelTTF::create(CCString::createWithFormat("%d", this->m_totalScore)->getCString(), "Corbel", 35.0f);
	this->m_labelScore->setPosition(ccp(0, 60));
	this->addChild(this->m_labelScore);

	this->m_labelLevel = CCLabelTTF::create(CCString::createWithFormat("%d", this->m_currentLevel)->getCString(), "Corbel", 35.0f);
	this->m_labelLevel->setPosition(ccp(0, -40));
	this->addChild(this->m_labelLevel);

	this->m_nextBlockImage = NULL;

	return true;
} //bool DisplayManager::init()

void DisplayManger::lineEliminated(int lineCount, BlockManager* sender)
{
	switch (lineCount)
	{
	case 1:
		this->_increaseScore(SCORE_1_LINE * m_currentLevel * 0.7);
		break;

	case 2:
		this->_increaseScore(SCORE_2_LINES * m_currentLevel * 0.7);
		break;

	case 3:
		this->_increaseScore(SCORE_3_LINES * m_currentLevel * 0.7);
		break;

	case 4:
		this->_increaseScore(SCORE_4_LINES * m_currentLevel * 0.7);

	default:
		break;
	}

	this->m_linesInCurrentLevel += lineCount;
	
	if (this->m_linesInCurrentLevel >= LINES_TO_UPGRADE && this->m_currentLevel <= MAX_LEVEL)
	{
		this->setLevel(++m_currentLevel, sender);
	}

} //void DisplayManger::lineEliminated(int lineCount)

void DisplayManger::nextBlockChanged(Block* block)
{
	if (this->m_nextBlockImage == NULL)
	{
		this->m_nextBlockImage = CCSprite::createWithTexture(block->getSprite()->getTexture());
		this->m_nextBlockImage->setPosition(ccp(0, 220));
		this->addChild(this->m_nextBlockImage);
	}
	else
	{
		this->m_nextBlockImage->setTexture(block->getSprite()->getTexture());
	}

	this->blockDropped();
} //void DisplayManger::nextBlockChanged(Block* block)

void DisplayManger::_increaseScore(int score)
{
	this->m_totalScore += score;
	this->m_labelScore->setString(CCString::createWithFormat("%d", this->m_totalScore)->getCString());
} //void DisplayManager::_scoreChanged(int score)

void DisplayManger::blockDropped()
{
	this->_increaseScore(m_currentLevel);
}

void DisplayManger::setLevel(int p_level, BlockManager* p_blockManager)
{
	this->m_linesInCurrentLevel %= 10;
	this->m_currentLevel = p_level;
	this->m_labelLevel->setString(CCString::createWithFormat("%d", this->m_currentLevel)->getCString());
	p_blockManager->setUpdateTime(BlockManager::DefaultRefreshTime / MAX_LEVEL * (MAX_LEVEL - m_currentLevel));
}