#pragma once
#include "GameObject.h"


class MovingObject : public GameObject
{
public:
	MovingObject(const sf::Sprite&);
	virtual ~MovingObject() = default;
	virtual void update(sf::Time) = 0;
	virtual void direction(sf::Keyboard::Key key) = 0;
	virtual void destroyBody() = 0;
	float getHealth();
    void setHealth(float h) ;
	void decreaseHealth(float h);
	bool isDead();
private:
	sf::Vector2f m_prevPosition;
	float m_health;
};