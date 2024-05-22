#pragma once
#include "Command.h"
#include "Menu.h"
#include "SinglePlayer.h"
#include "MultiPlayer.h"
#include "FriendlyFireOFF.h"
#include "FriendlyFireON.h"
#include "Back.h"

class StartGame : public Command
{
public:
	StartGame() {};
	~StartGame() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) override;
};