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
	this->m_blockManager = BlockManager::create(ccp(100, 200));

	this->addChild(m_blockManager);

	this->scheduleUpdate();

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
			switch (wParam)
			{
			case VK_LEFT:
				manager->pressedLeft();
				break; //case VK_LEFT

			case VK_RIGHT:
				manager->pressedRight();
				break; //case VK_RIGHT

			case VK_DOWN:
				manager->pressedDown();
				break; //case VK_DOWN

			case VK_UP:
				manager->pressedUp();
				break; //case VK_UP
			}
			manager->setKeyDownState(true);
			break; //case WM_KEYDOWN

		case WM_KEYUP:
			manager->setKeyDownState(false);
			break; //case WM_KEYUP
		}
	}
	

} //void TestScene::keyboardHook(UINT message, WPARAM wParam, LPARAM lParam)

TestScene* TestScene::getScene()
{
	return TestScene::m_scene;
}
