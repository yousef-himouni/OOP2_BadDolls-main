#pragma once
#include "Command.h"

class FriendlyFireON : public Command
{
public:
	FriendlyFireON() {};
	~FriendlyFireON() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;
};