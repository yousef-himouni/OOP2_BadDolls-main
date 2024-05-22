#pragma once
#include "Gift.h"
#include "Resources.h"

class HealingBall : public Gift
{
public:
	HealingBall(const sf::Sprite&);
	void update(sf::Time);
private:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};