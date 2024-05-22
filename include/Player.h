#pragma once

#include "MovingObject.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "io.h"
#include "Gun.h"
#include "Weapon.h"
#include "Bullet.h"

class Player : public MovingObject
{
public:
	Player() = default;
	Player(const sf::Sprite&);
	virtual void update(sf::Time) = 0;
	virtual void direction(sf::Keyboard::Key key) = 0;

	int getCoins()const;
	void setCoins(int);

	int getPoints()const;
	void setPoints(int);

	int getKills()const;
	void setKills(int);
	void addKills(int);

	void addWeapon(Weapon);
	Weapon& getWeapon(int index);
	int getWeaponCount();
	void changeWeaponDirection(sf::Keyboard::Key key);
	void clearChosenWeapon();

	void setIsJumping(bool);
	bool getIsJumping()const;

	void setCanJump(bool);
	bool getCanJump()const;

	void addBullet(Bullet);
	Bullet& getBullet(int index);
	void clearChosenBullet();

	virtual Direction getDirection() = 0;

private:
	int m_coins;
	int m_points;

	int m_kills;
	std::vector<Weapon> m_weapons;
	std::vector<Bullet> m_bullets;
	bool m_isJumping;
	bool m_canJump;

};