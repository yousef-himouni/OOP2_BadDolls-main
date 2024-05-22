#include "EnemyGhost.h"

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
EnemyGhost::EnemyGhost(const sf::Sprite& sprite, b2World* world) : m_world(world), Enemy(sprite),
m_animation(Resources::instance().animationData(Resources::EnemyGhost), Direction::Right, getSprite(), int(TextureTypes::enemyGhost))
{
    setHealth(GHOST_HEALTH);
    m_dynamicBodyDef.type = b2_dynamicBody;
    m_dynamicBodyDef.position.Set(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);
    m_dynamicBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_dynamicBody = m_world->CreateBody(&m_dynamicBodyDef);
    m_dynamicShape.SetAsBox(20.0f / SCALE, 20.0f / SCALE);
    m_dynamicFixtureDef.shape = &m_dynamicShape;
    m_dynamicFixtureDef.density = 1.0f;
    m_dynamicFixtureDef.friction = 0.3f;

    //trigger collision callbacks but will not have any solid interaction with other box2d objects.
    m_dynamicFixtureDef.isSensor = true;
    m_dynamicBody->CreateFixture(&m_dynamicFixtureDef);

    // Set the gravity scale to zero:
    m_dynamicBody->SetGravityScale(0.0f);

}
//-------------------------------------------------------------------------------------------
void EnemyGhost::update(sf::Time delta)
{
    b2Vec2 targetPosition;

    b2Vec2 ghostPosition = m_dynamicBody->GetPosition();
    // Calculate the distances to both players
    float distanceToFirstPlayer = std::sqrt(std::pow(m_firstPlayerPosition.x - ghostPosition.x, 2) +
        std::pow(m_firstPlayerPosition.y - ghostPosition.y, 2));
    float distanceToSecondPlayer = std::sqrt(std::pow(m_secondPlayerPosition.x - ghostPosition.x, 2) +
        std::pow(m_secondPlayerPosition.y - ghostPosition.y, 2));

    //If the bat closer to the first player, then he head to firstP:
    if (distanceToFirstPlayer <= distanceToSecondPlayer)
        targetPosition = m_firstPlayerPosition;
    else
        targetPosition = m_secondPlayerPosition;

    //round the position of the target:
    targetPosition.x = round(targetPosition.x);
    targetPosition.y = round(targetPosition.y);

    //round the position of the bat:
    ghostPosition.x = round(ghostPosition.x);
    ghostPosition.y = round(ghostPosition.y);

    //if the player is on the left of the bat:
    if (targetPosition.x < ghostPosition.x && targetPosition.y == ghostPosition.y)
    {
        velocity = b2Vec2(-1.2f, 0);
        direction(sf::Keyboard::Left);
    }

    //if the player is on the right of the bat:
    if (targetPosition.x > ghostPosition.x && targetPosition.y == ghostPosition.y)
    {
        velocity = b2Vec2(1.2f, 0.0f);
        direction(sf::Keyboard::Right);
    }

    //if the player is on top of the bat:
    if (targetPosition.x == ghostPosition.x && targetPosition.y < ghostPosition.y)
        velocity = b2Vec2(0.0f, -1.2f);

    //if the player is under of the bat:
    if (targetPosition.x == ghostPosition.x && targetPosition.y > ghostPosition.y)
        velocity = b2Vec2(0.0f, 1.2f);

    //if the player is left top of the bat:
    if (targetPosition.x < ghostPosition.x && targetPosition.y < ghostPosition.y)
    {
        velocity = b2Vec2(-1.2f, -1.2f);
        direction(sf::Keyboard::Left);
    }

    //if the player is right top of the bat:
    if (targetPosition.x > ghostPosition.x && targetPosition.y < ghostPosition.y)
    {
        velocity = b2Vec2(1.2f, -1.2f);
        direction(sf::Keyboard::Right);
    }
    //if the player is right buttom of the bat:
    if (targetPosition.x > ghostPosition.x && targetPosition.y > ghostPosition.y)
    {
        velocity = b2Vec2(1.2f, 1.2f);
        direction(sf::Keyboard::Right);
    }

    //if the player is left buttom of the bat:
    if (targetPosition.x < ghostPosition.x && targetPosition.y > ghostPosition.y)
    {
        velocity = b2Vec2(-1.2f, 1.2f);
        direction(sf::Keyboard::Left);
    }
    
    m_dynamicBody->SetLinearVelocity(velocity);
    setSpritePosition(sf::Vector2f(m_dynamicBody->GetPosition().x * SCALE, m_dynamicBody->GetPosition().y * SCALE));
    // Update the animation
    m_animation.update(delta);
}
//-------------------------------------------------------------------------------------------
void EnemyGhost::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//-------------------------------------------------------------------------------------------
void EnemyGhost::setFirstPlayerPosition(b2Vec2 firstPos)
{
    m_firstPlayerPosition = firstPos;
}
//-------------------------------------------------------------------------------------------
void EnemyGhost::setSecondPlayerPosition(b2Vec2 secondPos)
{
    m_secondPlayerPosition = (secondPos);
}
//-------------------------------------------------------------------------------------------
b2Vec2 EnemyGhost::getB2dPosition() const
{
    return m_dynamicBody->GetPosition();
}
//-------------------------------------------------------------------------------------------
void EnemyGhost::destroyBody()
{
    m_world->DestroyBody(m_dynamicBody);
    m_dynamicBody = nullptr;
}
