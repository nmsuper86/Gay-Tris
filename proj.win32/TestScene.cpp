#include "TestScene.h"


CCScene* TestScene::scene()
{
	CCScene* scene = CCScene::create();

	TestScene* layer = TestScene::create();

	scene->addChild(layer);

	return scene;
}

bool TestScene::init()
{
	this->m_blockManager = BlockManager::create(ccp(100, 200));

	this->addChild(m_blockManager);

//	this->scheduleUpdate();

	return true;
}

void TestScene::update(float delta)
{
	this->m_blockManager->update(delta);
}

