#pragma once
#include "Gift.h"

class Weapon : public Gift
{
private:
	bool m_chosen;
	Direction m_weaponDir;
	std::string m_weaponType;

public:
	Weapon(const sf::Sprite&, std::string weaponType);
	bool getChosen();
	void setChosen(bool);

	void setWeaponDir(Direction);
	Direction getWeaponDir();

	std::string getWeaponType();

};