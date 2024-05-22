#pragma once
#include "StaticObject.h"
#include <memory>

class Obstacle : public StaticObject
{
public:
	Obstacle(const sf::Sprite&);
	//virtual void setActivated(bool status) = 0;
	//virtual bool getActivated() const = 0;

private:
	//bool m_activated = false;

};