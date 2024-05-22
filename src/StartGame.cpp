#include "StartGame.h"

std::pair<ClickedButton, ClickedButton> StartGame::execute(sf::RenderWindow* window)
{
	auto playerModeMenu = Menu(window);
	playerModeMenu.add("Single Player Mode", std::make_unique<SinglePlayer>());
	playerModeMenu.add("Multiplayer Mode", std::make_unique<MultiPlayer>());
	playerModeMenu.add("Back", std::make_unique<Back>());

	auto choice = playerModeMenu.activate();

	while (true)
	{
		if (choice.first == ClickedButton::MultiPlayer)
		{
			auto friendlyFireMenu = Menu(window);
			friendlyFireMenu.add("Enable Friendly Fire", std::make_unique<FriendlyFireON>());
			friendlyFireMenu.add("Disable Friendly Fire", std::make_unique<FriendlyFireOFF>());
			friendlyFireMenu.add("Back", std::make_unique<Back>());
			auto friendlyFireChoice = friendlyFireMenu.activate();
			if (friendlyFireChoice.first == ClickedButton::Back)
			{
				choice = playerModeMenu.activate();  // Return to the previous line
				continue;  // Go back to the beginning of the loop
			}
			return { choice.first, friendlyFireChoice.first };
		}
		break;  // Exit the loop if choice.first is not MultiPlayer
	}

	return { choice.first, ClickedButton::Invalid };
}