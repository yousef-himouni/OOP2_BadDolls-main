#pragma once

#include "MovingObject.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "Enemy.h"
#include <optional>
#include "Direction.h"

class EnemySpider : public Enemy
{
public:
	EnemySpider(const sf::Sprite& sprite, b2World* world);
	virtual void update(sf::Time) override;
	virtual void direction(sf::Keyboard::Key key) override;
	virtual void destroyBody() override;
	Direction getDirection() const;
	b2Vec2 getB2dPosition() const;
	void bounce();
	
	Animation m_animation;
	b2World* m_world;
	b2BodyDef m_dynamicBodyDef;
	b2Body* m_dynamicBody;
	b2PolygonShape m_dynamicShape;
	b2FixtureDef m_dynamicFixtureDef;
	b2Vec2 velocity;


	Direction m_dir = Direction::Right;
};