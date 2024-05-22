#include "Bullet.h"

Bullet::Bullet(const sf::Sprite& sprite, Direction dir, std::string bulletType) :Gift(sprite), m_chosen(false), m_bulletDir(dir), m_bulletType(bulletType) {}

bool Bullet::getChosen()
{
	return m_chosen;
}

void Bullet::setChosen(bool c)
{
	m_chosen = c;
}

void Bullet::updateBullet(float delta)
{
	if (m_bulletDir == Direction::Right)
	{
		setSpriteOrigin({ 0.f,getSpriteHeight() / 2 });
	    setSpriteScale({ 1.f, 1.f });

		moveSprite(delta * sf::Vector2f(300.0f, 0.0f));
	}

	else if (m_bulletDir == Direction::Left)
	{
		setSpriteOrigin({ getSpriteWidth(), getSpriteHeight() / 2 });
		setSpriteScale({ -1.f, 1.f });

		moveSprite(delta * sf::Vector2f(-300.0f, 0.0f));
	}
}

std::string Bullet::getBulletType()
{
	return m_bulletType;
}

void Bullet::setBulletDir(Direction dir)
{
	if (dir == Direction::Right)
	{
		m_bulletDir = Direction::Right;
	}
	else if (dir == Direction::Left)
	{
		m_bulletDir = Direction::Left;
	}
}
Direction Bullet::getBulletDir()
{
	return m_bulletDir;
}

