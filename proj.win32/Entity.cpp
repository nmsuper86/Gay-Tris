#include "Entity.h"

Entity::Entity()
{
	m_sprite = NULL;
} //Entity::Entity()

Entity::~Entity()
{

} //Entity::~Entity()

CCSprite* Entity::getSprite()
{
	return this->m_sprite;
} //CCSprite* Entity::getSprite()

void Entity::bindSprite(CCSprite* sprite)
{
	this->m_sprite = sprite;
	this->addChild(sprite);
} //void Entiry::bindSprite()

