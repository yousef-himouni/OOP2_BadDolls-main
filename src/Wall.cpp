#include "Wall.h"
Wall::Wall(const sf::Sprite& sprite, b2World* world) : StaticObject(sprite), m_world(world)
{
    m_wallBodyDef.type = b2_staticBody;

    m_wallPos = b2Vec2(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);

    m_wallBodyDef.position = m_wallPos;
    m_wallBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    m_wallBody = m_world->CreateBody(&m_wallBodyDef);

    m_wallShape.SetAsBox(20.0f / SCALE, 20.0f / SCALE);
    m_wallFixtureDef.shape = &m_wallShape;
    m_wallFixtureDef.density = 0.0f;

    m_wallBody->CreateFixture(&m_wallFixtureDef);
    
}


b2Vec2 Wall::getB2dPosition() const
{
    return m_wallBody->GetPosition();
}


