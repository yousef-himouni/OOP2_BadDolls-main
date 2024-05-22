#include "SecondPlayer.h"
#include"FirstPlayer.h"
#include <optional>
#include "Direction.h"
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
        case sf::Keyboard::H:
            return Direction::Stay;
        }
        return {};
    }
}
//-------------------------------------------------------------------------------------------
SecondPlayer::SecondPlayer(const sf::Sprite& sprite, b2World* world) :m_world(world),  Player(sprite),
m_animation(Resources::instance().animationData(Resources::SecondPlayer), Direction::Right, getSprite(), int(TextureTypes::secondPlayer))
{
    setHealth(PLAYER_HEALTH);

    m_dynamicBodyDef.type = b2_dynamicBody;
    m_dynamicBodyDef.position.Set(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);
    m_dynamicBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_dynamicBody = m_world->CreateBody(&m_dynamicBodyDef);
    m_dynamicShape.SetAsBox(16.0f / SCALE, 16.0f / SCALE);
    m_dynamicFixtureDef.shape = &m_dynamicShape;
    m_dynamicFixtureDef.density = 1.0f;
    m_dynamicFixtureDef.friction = 0.3f;
    m_dynamicBody->CreateFixture(&m_dynamicFixtureDef);

    // Put the player to sleep
    m_dynamicBody->SetAwake(false);
}
//-------------------------------------------------------------------------------------------
void SecondPlayer::update(sf::Time delta)
{
    if (m_dir == Direction::Stay)
    {
        return;
    }

    if (m_dir == Direction::Up && !getIsJumping() && getCanJump())
    {
        Resources::instance().playSound(13);
        velocity = jumpImpulse;
        m_dynamicBody->ApplyLinearImpulse(velocity, m_dynamicBody->GetWorldCenter(), true);
        m_dynamicBody->SetLinearVelocity(velocity);
        setIsJumping(true);
        setCanJump(false);
    }
    if (m_dir == Direction::Left)
    {
        // Put the player to wake
        m_dynamicBody->SetAwake(true);
        velocity = b2Vec2(-5.0f, m_dynamicBody->GetLinearVelocity().y);
        m_dynamicBody->SetLinearVelocity(velocity);
    }
    else if (m_dir == Direction::Right)
    {
        // Put the player to wake
        m_dynamicBody->SetAwake(true);
        velocity = b2Vec2(5.0f, m_dynamicBody->GetLinearVelocity().y);
        m_dynamicBody->SetLinearVelocity(velocity);
    }

    setSpritePosition(sf::Vector2f(m_dynamicBody->GetPosition().x * SCALE, m_dynamicBody->GetPosition().y * SCALE));
    m_animation.update(delta);
}
//-------------------------------------------------------------------------------------------
void SecondPlayer::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//-------------------------------------------------------------------------------------------
void SecondPlayer::updateJumpStatus()
{
    if (getIsJumping() && m_dynamicBody->GetLinearVelocity().y >= 0.0f)
    {
        setIsJumping(false);
        setCanJump(false);
    }

    if (!getIsJumping() && m_dynamicBody->GetLinearVelocity().y == 0.0f)
    {
        setCanJump(true);
    }
}
//-------------------------------------------------------------------------------------------
void SecondPlayer::addHealth(int h)
{
    if (h + getHealth() > PLAYER_HEALTH)
        setHealth(PLAYER_HEALTH);
    else
        setHealth(h + getHealth());
}
//-------------------------------------------------------------------------------------------
void SecondPlayer::setDirection(Direction newDir)
{
    m_dir = newDir;
    m_animation.direction(newDir);
}
//-------------------------------------------------------------------------------------------
Direction SecondPlayer::getDirection()
{
    return m_dir;
}
//-------------------------------------------------------------------------------------------
void SecondPlayer::destroyBody()
{
    m_world->DestroyBody(m_dynamicBody);
    m_dynamicBody = nullptr;
}
//-------------------------------------------------------------------------------------------
b2Vec2 SecondPlayer::getB2dPosition() const
{
    return m_dynamicBody->GetPosition();
}

