#pragma once

#include "Gift.h"
#include "Resources.h"

class Heart : public Gift
{
public:
	Heart(const sf::Sprite&);
	void update(sf::Time);
private:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};