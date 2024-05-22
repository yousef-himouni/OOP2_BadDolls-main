#pragma once

#include "MovingObject.h"
#include <memory>
#include "Animation.h"
#include "Resources.h"
#include "Enemy.h"
#include <optional>
#include "Direction.h"

class EnemyGhost : public Enemy
{
public:
	EnemyGhost(const sf::Sprite&, b2World* world);

	virtual void update(sf::Time) override;
	virtual void direction(sf::Keyboard::Key key) override;

	virtual void destroyBody() override;

	void setFirstPlayerPosition(b2Vec2 firstPos);
	void setSecondPlayerPosition(b2Vec2 secondPos);
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


	b2Vec2 m_firstPlayerPosition;
	b2Vec2 m_secondPlayerPosition;
};