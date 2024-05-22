#pragma once

#include "MovingObject.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "Player.h"

class SecondPlayer : public Player
{
public:
	SecondPlayer(const sf::Sprite& sprite, b2World* world);
	virtual void update(sf::Time) override;
	virtual void direction(sf::Keyboard::Key key) override;
	virtual void destroyBody() override;
	void addHealth(int h);

	void updateJumpStatus();

	void setDirection(Direction newDir);
	Direction getDirection();

	
	b2Vec2 getB2dPosition() const;

private:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
	b2World* m_world;

	b2BodyDef m_dynamicBodyDef;
	b2Body* m_dynamicBody;
	b2PolygonShape m_dynamicShape;
	b2FixtureDef m_dynamicFixtureDef;
	b2Vec2 velocity;
};