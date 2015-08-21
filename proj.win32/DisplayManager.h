#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d;

class DisplayManger:public CCNode
{
public:
	DisplayManger();
	~DisplayManger();

	CREATE_FUNC(DisplayManger);
	virtual bool init();

public:
	virtual void lineEliminated();
	virtual void nextBlockChanged(Block* block);

}; //class DisplayManager

#endif