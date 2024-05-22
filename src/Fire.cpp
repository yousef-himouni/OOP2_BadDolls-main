#include "Fire.h"

Fire::Fire(const sf::Sprite& sprite) :Obstacle(sprite),
m_animation(Resources::instance().animationData(Resources::Fire), Direction::Stay, getSprite(), int(TextureTypes::fire)) {}


void Fire::update(sf::Time delta)
{
	m_animation.update(delta);
}
