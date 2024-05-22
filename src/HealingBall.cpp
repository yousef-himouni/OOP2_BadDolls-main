#include "HealingBall.h"

HealingBall::HealingBall(const sf::Sprite& sprite) :Gift(sprite),
m_animation(Resources::instance().animationData(Resources::HealingBall), Direction::Stay, getSprite(), int(TextureTypes::healingBall)) {}


void HealingBall::update(sf::Time delta)
{
	m_animation.update(delta);
}
