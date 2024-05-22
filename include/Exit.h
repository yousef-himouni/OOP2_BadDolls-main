#pragma once
#include "Command.h"


class Exit : public Command
{
public:
	Exit() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;

};