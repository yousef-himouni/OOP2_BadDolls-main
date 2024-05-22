#pragma once
#include "Command.h"


class Next : public Command
{
public:
	Next() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;

};