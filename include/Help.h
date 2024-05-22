#pragma once
#include "Command.h"
#include "Menu.h"
#include "Next.h"

class Help : public Command
{
public:
	Help() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;

};