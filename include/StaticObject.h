#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"


class StaticObject : public GameObject
{
public:
	StaticObject(const sf::Sprite&);

	void deleteObject();
	bool getDelete();

private:
	bool m_delete;
};