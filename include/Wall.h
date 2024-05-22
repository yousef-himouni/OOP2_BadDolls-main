#pragma once
#include "StaticObject.h"
#include "Resources.h"
#include <memory>

class Wall : public StaticObject
{
private:
	b2World* m_world;

	b2Body* m_wallBody;
	b2BodyDef m_wallBodyDef;
	b2Vec2 m_wallPos;
	b2PolygonShape m_wallShape;
	b2FixtureDef m_wallFixtureDef;

public:
	
	Wall(const sf::Sprite&, b2World* world);
	b2Vec2 getB2dPosition() const;
};
