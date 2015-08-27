#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class TestScene:public CCLayer
{
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(TestScene);
};

#endif //__TEST_SCENE_H__