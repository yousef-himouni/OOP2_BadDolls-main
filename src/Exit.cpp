#include "Exit.h"


std::pair<ClickedButton, ClickedButton> Exit::execute(sf::RenderWindow* window)
{
	exit(EXIT_SUCCESS);
}