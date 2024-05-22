#include "EnemySpider.h"

//-------------------------------------------------------------------------------------------
namespace
{
    std::optional<Direction> toDirection(sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::Left:
            return Direction::Left;
        case sf::Keyboard::Right:
            return Direction::Right;
        case sf::Keyboard::Up:
            return Direction::Up;
        case sf::Keyboard::Down:
            return Direction::Down;
        case sf::Keyboard::Space:
            return Direction::Stay;
        }
        return {};
    }
}
//-------------------------------------------------------------------------------------------
EnemySpider::EnemySpider(const sf::Sprite& sprite, b2World* world) : m_world(world), Enemy(sprite),
m_animation(Resources::instance().animationData(Resources::EnemySpider), Direction::Right, getSprite(), int(TextureTypes::enemySpider))
{
    setHealth(SPIDER_HEALTH);

    m_dynamicBodyDef.type = b2_dynamicBody;
    m_dynamicBodyDef.position.Set(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);
    m_dynamicBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_dynamicBody = m_world->CreateBody(&m_dynamicBodyDef);
    m_dynamicShape.SetAsBox(20.0f / SCALE, 20.0f / SCALE);
    m_dynamicFixtureDef.shape = &m_dynamicShape;
    m_dynamicFixtureDef.density = 1.0f;
    m_dynamicFixtureDef.friction = 0.3f;
    m_dynamicBody->CreateFixture(&m_dynamicFixtureDef);
}
//-------------------------------------------------------------------------------------------
void EnemySpider::update(sf::Time delta)
{
    if (m_dir == Direction::Left)
    {
        velocity = b2Vec2(-2.5f, m_dynamicBody->GetLinearVelocity().y);
        m_dynamicBody->SetLinearVelocity(velocity);
    }
    else if (m_dir == Direction::Right)
    {
        velocity = b2Vec2(2.5f, m_dynamicBody->GetLinearVelocity().y);
        m_dynamicBody->SetLinearVelocity(velocity);
    }

    setSpritePosition(sf::Vector2f(m_dynamicBody->GetPosition().x * SCALE, m_dynamicBody->GetPosition().y * SCALE));
    m_animation.update(delta);
}
//-------------------------------------------------------------------------------------------
void EnemySpider::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//-------------------------------------------------------------------------------------------
Direction EnemySpider::getDirection() const
{
    return m_dir;
}
//-------------------------------------------------------------------------------------------
b2Vec2 EnemySpider::getB2dPosition() const
{
    return m_dynamicBody->GetPosition();
}
//-------------------------------------------------------------------------------------------
void EnemySpider::bounce()
{
    if(m_dir == Direction::Left)
    {
        velocity = b2Vec2(-2.0f, m_dynamicBody->GetLinearVelocity().y + 0.15f);
        m_dynamicBody->ApplyLinearImpulse(velocity, m_dynamicBody->GetWorldCenter(), true);
    }
    else if (m_dir == Direction::Right)
    {
        velocity = b2Vec2(-2.0f, m_dynamicBody->GetLinearVelocity().y + 0.15f);
        m_dynamicBody->ApplyLinearImpulse(velocity, m_dynamicBody->GetWorldCenter(), true);
    }
}
//-------------------------------------------------------------------------------------------
void EnemySpider::destroyBody()
{
    m_world->DestroyBody(m_dynamicBody);
    m_dynamicBody = nullptr;
}