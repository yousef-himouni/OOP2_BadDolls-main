#pragma once
#include "io.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Resources.h"
class GameObject
{
public:
	GameObject(const sf::Sprite&);
	virtual ~GameObject() = default;

	sf::Sprite& getSprite();
	void setSprite(sf::Sprite);
	
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f);

	void setPrevPosition(sf::Vector2f pos);
	sf::Vector2f getPrevPosition() const;
	void draw(sf::RenderWindow* window);

	b2Body* getB2DBody();

	void setLvlSize(sf::Vector2f newLvl);
	sf::Vector2f getLvlSize() const;


	//operations on sprite:

	void setSpriteOrigin(sf::Vector2f newOrigin);
	void setSpriteScale(sf::Vector2f newScale);
	void setSpritePosition(sf::Vector2f newPosition);

	void moveSprite(sf::Vector2f offset);

	float getSpriteHeight() const;
	float getSpriteWidth() const;
	
	sf::FloatRect getSpriteBounds() const;

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_prevPosition;
	sf::Vector2f m_boardLvlSize;
	b2Body* m_b2dBody;
};