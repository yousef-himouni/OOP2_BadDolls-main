#include "Obstacle.h"

class Fire : public Obstacle
{
public:
	Fire(const sf::Sprite&);
	void update(sf::Time);
private:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
};