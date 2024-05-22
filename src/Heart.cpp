#include "Heart.h"

Heart::Heart(const sf::Sprite& sprite) :Gift(sprite),
m_animation(Resources::instance().animationData(Resources::Heart), Direction::Stay, getSprite(), int(TextureTypes::heart)) {}


void Heart::update(sf::Time delta)
{
	m_animation.update(delta);
}
