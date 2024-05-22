#include "Coin.h"

Coin::Coin(const sf::Sprite& sprite) :Gift(sprite),
m_animation(Resources::instance().animationData(Resources::Coin), Direction::Stay, getSprite(), int(TextureTypes::coin)) {}


void Coin::update(sf::Time delta)
{
	m_animation.update(delta);
}
