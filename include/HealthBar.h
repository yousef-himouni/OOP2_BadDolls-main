#pragma once
#include "Resources.h"

const float ORIGINAL_WIDTH = 32.0f;
const float ORIGINAL_HEIGHT = 6.0f;

class HealthBar
{
private:
	sf::RectangleShape m_bar;
	sf::RectangleShape m_outFrame;
	sf::Vector2f m_position;
	float m_maxHealth;

public:
	HealthBar(sf::Vector2f position, float maxHealth);
	void setBarWidth(float health);
	void setPosition(sf::Vector2f position);
	void drawHealthBar(sf::RenderWindow* window);
};