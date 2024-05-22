#pragma once

#include "Gift.h"
#include "Resources.h"

class Coin : public Gift
{
public:
	Coin(const sf::Sprite&);
	void update(sf::Time);

private:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};