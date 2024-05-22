#pragma once
#include "Resources.h"
#include "io.h"
#include "GameObject.h"
#include "StaticObject.h"
#include "Wall.h"
#include "Player.h"
#include "FirstPlayer.h"
#include "SecondPlayer.h"
#include "MovingObject.h"
#include "Controller.h"
#include <vector>
#include <memory>
#include <exception>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "CollisionHandling.h"
#include "EnemySpider.h"
#include "Heart.h"
#include <iostream>
#include "Coin.h"
#include "EnemyBat.h"
#include "Gun.h"
#include "Weapon.h"
#include "Sniper.h"
#include "HealthBar.h"
#include "ContactListener.h"
#include "GunBullet.h"
#include "sniperBullet.h"
#include "Bullet.h"
#include "Throns.h"
#include "Fire.h"
#include "HealingBall.h"
#include "EnemyGhost.h"
#include "GhostHouse.h"
#include "EnemyHouse.h"
#include "BatsHouse.h"

class Board
{

public:

	//constructor:
	Board(const sf::RenderWindow*, const int, ContactListener& listener);
	~Board() {};
	void draw(sf::RenderWindow*);
	void drawInfo(sf::RenderWindow*);
	void updateMoving(sf::Time);
	void updateStatics(sf::Time);
	void updateBullets(sf::Time);
	void updateWeapons();
	void updateJumpStatus();
	void directionPlayers(sf::Keyboard::Key first, sf::Keyboard::Key second);
	void changeWeapon(bool first, bool second);
	void collision();
	bool collide(GameObject& a, GameObject& b);
	void handleBoard();
	void stepWorld();
	void shoot(bool, bool);
	void shootForPlayer(Player&);



	//templated function:
	//================================================================
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
	{
		for (; begin != end; ++begin)
			for (auto second = begin + 1; second != end; ++second)
				fn(*begin, *second);

	}
	//================================================================

private:
	sf::RectangleShape m_board;
	sf::Vector2f m_levelSize;
	sf::Vector2f m_levelPosition;
	sf::Sprite m_backGround;
	sf::Sprite m_coinsFirst;
	sf::Sprite m_coinsSecond;
	sf::Sprite m_bulletsFirst;
	sf::Sprite m_bulletsSecond;
	sf::Sprite m_firstPlayerPoints;
	sf::Sprite m_secondPlayerPoints;

	std::vector<std::unique_ptr<MovingObject>> m_movingObjects;
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
	std::vector<HealthBar> m_healthBars;
	std::vector<std::unique_ptr<Bullet>> m_bullets;

	sf::Sprite m_gunBulletSprite, m_sniperBulletSprite;
	sf::Sprite m_ghost, m_bat;
	//box2d world for the game physics:
	std::unique_ptr<b2World> m_world;

	std::vector<sf::Sprite> m_livesObjects;
	void makeObject(const ObjectTypes&, const sf::Vector2f&, b2World* world);

	sf::Vector2f m_ghostsHousePos,m_batsHousePos;
	sf::Clock m_creatingBatsTimer, m_creatingGhostsTimer;
	//Board Helping Functions:
	float Xposition(const int) const;
	float Yposition(const int) const;

	static std::unique_ptr<MovingObject> createMovingObject(ObjectTypes type,
		const sf::Vector2f& position,
		const std::vector<sf::Texture>& textures, b2World* world);

	static std::unique_ptr<StaticObject> createStaticObject(ObjectTypes type,
		const sf::Vector2f& position,
		const std::vector<sf::Texture>& textures, b2World* world);
	void createGhost(sf::Vector2f);
	void createBat();
	b2Vec2 findFirstPlayer();
	b2Vec2 findSecondPlayer();

	bool m_batHouseExists, m_ghostHouseExists;
};