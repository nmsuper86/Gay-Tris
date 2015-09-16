#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "cocos2d.h"
#include "Block.h"

#define SCORE_1_LINE 10
#define SCORE_2_LINES 40
#define SCORE_3_LINES 160
#define SCORE_4_LINES 640

#define LINES_TO_UPGRADE 10
#define MAX_LEVEL 20

using namespace cocos2d;

class BlockManager;

class DisplayManger:public CCNode
{
protected:
	int m_currentLevel;
	int m_totalScore;
	int m_linesInCurrentLevel;

	CCLabelTTF* m_labelScore;
	CCLabelTTF* m_labelLevel;
	CCSprite* m_nextBlockImage;

public:
	DisplayManger();
	~DisplayManger();

	CREATE_FUNC(DisplayManger);
	virtual bool init();

public:
	virtual void lineEliminated(int lineCount, BlockManager* sender);
	virtual void nextBlockChanged(Block* block);
	virtual void blockDropped();
	virtual void setLevel(int p_level, BlockManager* p_blockManager);

protected:
	virtual void _increaseScore(int score);

}; //class DisplayManager

#endif