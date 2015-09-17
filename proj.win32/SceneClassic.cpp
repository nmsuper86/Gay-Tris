#include "SceneClassic.h"

SceneClassic* SceneClassic::m_scene = NULL;

CCScene* SceneClassic::scene()
{
	CCScene* scene = CCScene::create();

	SceneClassic* layer = SceneClassic::create();

	SceneClassic::m_scene = layer;

	scene->addChild(layer);

	return scene;
}

bool SceneClassic::init()
{
	this->m_displayManager = DisplayManger::create();

	this->m_displayManager->setPosition(650, 270);

	this->addChild(this->m_displayManager);

	this->m_blockManager = BlockManager::create(ccp(250, 300), m_displayManager);

	this->addChild(m_blockManager);

	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook(SceneClassic::keyboardHook);

	return true;
}

BlockManager* SceneClassic::getManager()
{
	return this->m_blockManager;
}

void SceneClassic::keyboardHook(UINT message, WPARAM wParam, LPARAM lParam)
{
	static BlockManager* manager = SceneClassic::getScene()->getManager();

	if (manager)
	{
		switch (message)
		{
		case WM_KEYDOWN:
			manager->triggerKeyboard(wParam);
			break; //case WM_KEYDOWN

		case WM_KEYUP:
			manager->setKeyboardState(false);
			break; //case WM_KEYUP
		}
	}


} //void SceneClassic::keyboardHook(UINT message, WPARAM wParam, LPARAM lParam)

SceneClassic* SceneClassic::getScene()
{
	return SceneClassic::m_scene;
}
