#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

using namespace cocos2d;

class Entity:public CCNode
{
public:
	Entity();
	~Entity();
	CCSprite* getSprite();
	void bindSprite(CCSprite* sprite);

private:
	CCSprite* m_sprite;
}; //class Entity

#endif //__ENTITY_H__