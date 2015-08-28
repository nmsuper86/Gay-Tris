#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "BlockManager.h"

using namespace cocos2d;

class TestScene:public CCLayer
{
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(TestScene);

	void update(float delta);

private:
	BlockManager* m_blockManager;
};

#endif //__TEST_SCENE_H__