#include "MovingObject.h"
#include <iostream>

MovingObject::MovingObject(const sf::Sprite& sprite):GameObject(sprite) {}

float MovingObject::getHealth()
{
    return m_health;
}
void MovingObject::setHealth(float h)
{
    m_health = h;
}
void MovingObject::decreaseHealth(float h)
{
    m_health -= h;
}
bool MovingObject::isDead()
{
    return m_health <= 0;
}
//-------------------------------------------------------------------------------------------


