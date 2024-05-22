#include "Player.h"

Player::Player(const sf::Sprite& sprite) :MovingObject(sprite), m_coins(0), m_points(0),
m_isJumping(false), m_canJump(true)
{

}

int Player::getCoins()const
{
    return m_coins;
}

void Player::setCoins(int c)
{
    m_coins += c;
}

int Player::getPoints()const
{
    return m_points;
}

void Player::setPoints(int p)
{
    m_points += p;
}

int Player::getKills() const
{
    return m_kills;
}
void Player::setKills(int k)
{
    m_kills = k;
}
void Player::addKills(int k)
{
    m_kills += k;
}
void Player::addWeapon(Weapon weapon)
{
    for (auto& weaponObj : m_weapons)
    {
        if (weaponObj.getWeaponType() == weapon.getWeaponType())
            return;
    }
    m_weapons.push_back(weapon);
}

Weapon& Player::getWeapon(int index)
{
    if (index < 0 || index >= m_weapons.size())
    {
        throw std::out_of_range("Invalid gun index");
    }

    return m_weapons[index];
}

int Player::getWeaponCount()
{
    return m_weapons.size();
}

//change the direction of the weapon according to the direction of the player
void Player::changeWeaponDirection(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Right || key == sf::Keyboard::D)
    {
        for (size_t i = 0; i < m_weapons.size(); i++)
        {
            m_weapons[i].setSpriteOrigin({0.f, m_weapons[i].getSpriteHeight() / 2});
            m_weapons[i].setSpriteScale({ 1.f, 1.f });

        }
    }
    else if (key == sf::Keyboard::Left || key == sf::Keyboard::A)
    {
        for (size_t i = 0; i < m_weapons.size(); i++)
        {
            m_weapons[i].setSpriteOrigin({ m_weapons[i].getSpriteWidth(),  m_weapons[i].getSpriteHeight() / 2 });
            m_weapons[i].setSpriteScale({ -1.f, 1.f });

           
        }
    }
}




void Player::clearChosenWeapon()
{
    for (auto& weapon : m_weapons)
    {
        weapon.setChosen(false);
    }
}

void Player::setIsJumping(bool j)
{
    m_isJumping = j;
}

bool Player::getIsJumping()const
{
    return m_isJumping;
}

void Player::setCanJump(bool j)
{
    m_canJump = j;
}

bool Player::getCanJump()const
{
    return m_canJump;
}

void Player::addBullet(Bullet bullet)
{
    m_bullets.push_back(bullet);
}

Bullet& Player::getBullet(int index)
{
    if (index < 0 || index >= m_bullets.size())
    {
        throw std::out_of_range("Invalid gun index");
    }

    return m_bullets[index];
}

void Player::clearChosenBullet()
{
    for (auto& bullet : m_bullets)
    {
        bullet.setChosen(false);
    }
}




