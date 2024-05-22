#pragma once

#include "io.h"
#include "Resources.h"
#include <memory>

class Command
{
public:

	Command() {};
	virtual std::pair<ClickedButton, ClickedButton> execute(sf::RenderWindow* window) = 0;
	//virtual ~Command() = default;
};