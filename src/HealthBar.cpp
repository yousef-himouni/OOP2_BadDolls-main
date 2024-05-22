#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f position, float maxHealth):m_position(position), m_maxHealth(maxHealth)
{
	m_outFrame.setSize(sf::Vector2f(ORIGINAL_WIDTH + 2.0f, ORIGINAL_HEIGHT + 2.0f));
	m_bar.setSize(sf::Vector2f(ORIGINAL_WIDTH, ORIGINAL_HEIGHT));

	m_outFrame.setOutlineColor(sf::Color::Black);
	m_outFrame.setOutlineThickness(2.0f);
	m_outFrame.setFillColor(sf::Color::Transparent);
	m_outFrame.setPosition(sf::Vector2f(position.x, position.y - 5));

	m_bar.setFillColor(sf::Color::Green);
	m_bar.setPosition(sf::Vector2f(position.x + 1, position.y -4));
}

void HealthBar::setBarWidth(float health)
{
	m_bar.setSize(sf::Vector2f((health / m_maxHealth) * ORIGINAL_WIDTH, ORIGINAL_HEIGHT));
	if ((health / m_maxHealth) <= 0.3f)
	{
		m_bar.setFillColor(sf::Color::Red);
	}
	else if ((health / m_maxHealth) > 0.3f && (health / m_maxHealth) <= 0.7f)
	{
		m_bar.setFillColor(sf::Color(255,165,0));
	}
	else if ((health / m_maxHealth) > 0.7f && (health / m_maxHealth) <= 1.0f)
	{
		m_bar.setFillColor(sf::Color::Green);
	}
}

void HealthBar::setPosition(sf::Vector2f position)
{
	m_outFrame.setPosition(sf::Vector2f(position.x , position.y - 5));
	m_bar.setPosition(sf::Vector2f(position.x + 1, position.y - 4));
}

void HealthBar::drawHealthBar(sf::RenderWindow* window)
{
	window->draw(m_outFrame);
	window->draw(m_bar);
}
