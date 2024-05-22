#include "Weapon.h"

Weapon::Weapon(const sf::Sprite& sprite, std::string weaponType) :Gift(sprite), m_chosen(false), m_weaponType(weaponType){}

bool Weapon::getChosen()
{
	return m_chosen;
}

void Weapon::setChosen(bool c)
{
	m_chosen = c;
}

void Weapon::setWeaponDir(Direction dir)
{
	if (dir == Direction::Right)
	{
		m_weaponDir = Direction::Right;
	}
	else if (dir == Direction::Left)
	{
		m_weaponDir = Direction::Left;
	}
}

Direction Weapon::getWeaponDir()
{
	return m_weaponDir;
}

std::string Weapon::getWeaponType()
{
	return m_weaponType;
}
