#include "TestScene.h"

TestScene* TestScene::m_scene = NULL;

CCScene* TestScene::scene()
{
	CCScene* scene = CCScene::create();

	TestScene* layer = TestScene::create();

	TestScene::m_scene = layer;

	scene->addChild(layer);

	return scene;
}

bool TestScene::init()
{
	this->m_displayManager = DisplayManger::create();

	this->m_displayManager->setPosition(650, 270);

	this->addChild(this->m_displayManager);

	this->m_blockManager = BlockManager::create(ccp(250, 300), m_displayManager);

	this->addChild(m_blockManager);

	this->m_displayManager->setLevel(20, m_blockManager);

	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook(TestScene::keyboardHook);

	return true;
}

void TestScene::update(float delta)
{
	this->m_blockManager->update(delta);
}

BlockManager* TestScene::getManager()
{
	return this->m_blockManager;
}

void TestScene::keyboardHook(UINT message, WPARAM wParam, LPARAM lParam)
{
	static BlockManager* manager = TestScene::getScene()->getManager();

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
	

} //void TestScene::keyboardHook(UINT message, WPARAM wParam, LPARAM lParam)

TestScene* TestScene::getScene()
{
	return TestScene::m_scene;
}
