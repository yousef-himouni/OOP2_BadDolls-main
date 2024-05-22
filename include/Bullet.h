#pragma once
#include "Resources.h"
#include "Gift.h"

class Bullet : public Gift
{
private:
	bool m_chosen;
	Direction m_bulletDir;
	std::string m_bulletType;
public:
	Bullet(const sf::Sprite&, Direction, std::string);
	bool getChosen();
	void setChosen(bool);
	void updateBullet(float delta);
	std::string getBulletType();

	void setBulletDir(Direction);
	Direction getBulletDir();
};