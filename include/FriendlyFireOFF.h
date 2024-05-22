#pragma once
#include "Command.h"

class FriendlyFireOFF : public Command
{
public:
	FriendlyFireOFF() {};
	~FriendlyFireOFF() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;
};