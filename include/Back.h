#pragma once
#include "Command.h"


class Back : public Command
{
public:
	Back() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;

};