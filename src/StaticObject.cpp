#include "StaticObject.h"

StaticObject::StaticObject(const sf::Sprite& sprite):GameObject(sprite)
{
	m_delete = false;
}
//-------------------------------------------------------------------------------------------
void StaticObject::deleteObject()
{
	m_delete = true;
}
//-------------------------------------------------------------------------------------------
bool StaticObject::getDelete()
{
	return m_delete;
}
//-------------------------------------------------------------------------------------------