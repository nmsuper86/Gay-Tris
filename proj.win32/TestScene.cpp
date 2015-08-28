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
	this->m_blockManager = BlockManager::create();

	m_blockManager->setPosition(ccp(400, 400));

	this->addChild(m_blockManager);

	this->scheduleUpdate();

	return true;
}

void TestScene::update(float delta)
{
	CCLog(CCStringMake("F%d", this->m_blockManager)->getCString());
	this->m_blockManager->update(delta);
	CCLog(CCStringMake("R%d", this->m_blockManager)->getCString());
}

