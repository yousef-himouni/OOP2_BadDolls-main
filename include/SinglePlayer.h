#pragma once
#include "Command.h"


class SinglePlayer : public Command
{
public:
	SinglePlayer() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;

};