#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "BlockManager.h"
#include <windows.h>

using namespace cocos2d;

class TestScene:public CCLayer
{
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(TestScene);

	void update(float delta);

	BlockManager* getManager();

	static void keyboardHook(UINT message, WPARAM wParam, LPARAM lParam);

	static TestScene* getScene();

private:
	BlockManager* m_blockManager;

	static TestScene* m_scene;
	
};

#endif //__TEST_SCENE_H__