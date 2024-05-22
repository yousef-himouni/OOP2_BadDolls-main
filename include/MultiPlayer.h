#pragma once

#include "Command.h"

class MultiPlayer : public Command
{
public:
	MultiPlayer() {};
	~MultiPlayer() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;
};