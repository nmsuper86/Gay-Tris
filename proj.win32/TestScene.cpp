#include "TestScene.h"
#include "BlockManager.h"

CCScene* TestScene::scene()
{
	CCScene* scene = CCScene::create();

	TestScene* layer = TestScene::create();

	scene->addChild(layer);

	return scene;
}

bool TestScene::init()
{
	BlockManager* manager = BlockManager::create();

	manager->setPosition(ccp(400, 400));

	this->addChild(manager);

	return true;
}