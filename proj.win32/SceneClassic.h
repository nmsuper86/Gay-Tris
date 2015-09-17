#ifndef __GAME_SCENE_CLASSIC_H__
#define __GAME_SCENE_CLASSIC_H__

#include "cocos2d.h"
#include "BlockManager.h"
#include "DisplayManager.h"
#include <windows.h>

using namespace cocos2d;

class SceneClassic :public CCLayer
{
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(SceneClassic);

	BlockManager* getManager();

	static void keyboardHook(UINT message, WPARAM wParam, LPARAM lParam);

	static SceneClassic* getScene();

private:
	BlockManager* m_blockManager;
	DisplayManger* m_displayManager;

	static SceneClassic* m_scene;

};

#endif //__GAME_SCENE_CLASSIC_H__