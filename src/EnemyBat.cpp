#include "EnemyBat.h"


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
EnemyBat::EnemyBat(const sf::Sprite& sprite, b2World* world) : m_world(world),Enemy(sprite),
m_animation(Resources::instance().animationData(Resources::EnemyBat), Direction::Right, getSprite(), int(TextureTypes::enemyBat)) 
{
    setHealth(BAT_HEALTH);
    m_dynamicBodyDef.type = b2_dynamicBody;
    m_dynamicBodyDef.position.Set(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);
    m_dynamicBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_dynamicBody = m_world->CreateBody(&m_dynamicBodyDef);
    m_dynamicShape.SetAsBox(16.0f / SCALE, 16.0f / SCALE);
    m_dynamicFixtureDef.shape = &m_dynamicShape;
    m_dynamicFixtureDef.density = 1.0f;
    m_dynamicFixtureDef.friction = 0.3f;
    m_dynamicBody->CreateFixture(&m_dynamicFixtureDef);

    // Set the gravity scale to zero
    m_dynamicBody->SetGravityScale(0.0f);

}
//-------------------------------------------------------------------------------------------
void EnemyBat::update(sf::Time delta)
{
    b2Vec2 targetPosition;
    
    b2Vec2 batPosition = m_dynamicBody->GetPosition();
    // Calculate the distances to both players
    float distanceToFirstPlayer = std::sqrt(std::pow(m_firstPlayerPosition.x - batPosition.x, 2) +
        std::pow(m_firstPlayerPosition.y - batPosition.y, 2));
    float distanceToSecondPlayer = std::sqrt(std::pow(m_secondPlayerPosition.x - batPosition.x, 2) +
        std::pow(m_secondPlayerPosition.y - batPosition.y, 2));

    //If the bat closer to the first player, then he head to firstP:
    if (distanceToFirstPlayer <= distanceToSecondPlayer)
        targetPosition = m_firstPlayerPosition;
    else
        targetPosition = m_secondPlayerPosition;

    //round the position of the target:
    targetPosition.x = round(targetPosition.x);
    targetPosition.y = round(targetPosition.y);

    //round the position of the bat:
    batPosition.x = round(batPosition.x);
    batPosition.y = round(batPosition.y);

    //if the player is on the left of the bat:
    if (targetPosition.x < batPosition.x && targetPosition.y == batPosition.y)
        velocity = b2Vec2(-2.0f ,0 );

    //if the player is on the right of the bat:
    if (targetPosition.x > batPosition.x && targetPosition.y == batPosition.y)
        velocity = b2Vec2(2.0f, 0.0f);

    //if the player is on top of the bat:
    if (targetPosition.x == batPosition.x && targetPosition.y < batPosition.y)
        velocity = b2Vec2(0.0f, -2.0f);

    //if the player is under of the bat:
    if (targetPosition.x == batPosition.x && targetPosition.y > batPosition.y)
        velocity = b2Vec2(0.0f, 2.0f);

    //if the player is left top of the bat:
    if (targetPosition.x < batPosition.x && targetPosition.y < batPosition.y)
        velocity = b2Vec2(-2.0f, -2.0f);

    //if the player is right top of the bat:
    if (targetPosition.x > batPosition.x && targetPosition.y < batPosition.y)
        velocity = b2Vec2(2.0f, -2.0f);

    //if the player is right buttom of the bat:
    if (targetPosition.x > batPosition.x && targetPosition.y > batPosition.y)
        velocity = b2Vec2(2.0f, 2.0f);

    //if the player is left buttom of the bat:
    if (targetPosition.x < batPosition.x && targetPosition.y > batPosition.y)
        velocity = b2Vec2(-2.0f, 2.0f);


    m_dynamicBody->SetLinearVelocity(velocity);
    setSpritePosition(sf::Vector2f(m_dynamicBody->GetPosition().x * SCALE, m_dynamicBody->GetPosition().y * SCALE));
    // Update the animation
    m_animation.update(delta);
}
//-------------------------------------------------------------------------------------------
void EnemyBat::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//-------------------------------------------------------------------------------------------
void EnemyBat::setFirstPlayerPosition(b2Vec2 firstPos)
{
    m_firstPlayerPosition = firstPos;
}
//-------------------------------------------------------------------------------------------
void EnemyBat::setSecondPlayerPosition(b2Vec2 secondPos)
{
    m_secondPlayerPosition = (secondPos);
}
//-------------------------------------------------------------------------------------------
void EnemyBat::bounce(Direction bounceDirection)
{
    if (m_dir == Direction::Left)
    {
        velocity = b2Vec2(-1.0f, m_dynamicBody->GetLinearVelocity().y);
        m_dynamicBody->ApplyLinearImpulse(velocity, m_dynamicBody->GetWorldCenter(), true);
    }
    else if (m_dir == Direction::Right)
    {
        velocity = b2Vec2(1.0f, m_dynamicBody->GetLinearVelocity().y);
        m_dynamicBody->ApplyLinearImpulse(velocity, m_dynamicBody->GetWorldCenter(), true);
    }
}
//-------------------------------------------------------------------------------------------
b2Vec2 EnemyBat::getB2dPosition() const
{
    return m_dynamicBody->GetPosition();
}
//-------------------------------------------------------------------------------------------
void EnemyBat::destroyBody() 
{
    m_world->DestroyBody(m_dynamicBody);
    m_dynamicBody = nullptr;
}
