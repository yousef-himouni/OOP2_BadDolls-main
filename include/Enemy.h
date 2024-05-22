#pragma once

#include "MovingObject.h"
#include "Animation.h"
#include "Resources.h"
#include "io.h"
#include <memory>

class Enemy : public MovingObject
{
public:
	Enemy() = default;
	Enemy(const sf::Sprite&);
	virtual void update(sf::Time) = 0;
	virtual void direction(sf::Keyboard::Key key) = 0;
private:
};