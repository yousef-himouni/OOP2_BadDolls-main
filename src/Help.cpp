#include "Help.h"



std::pair<ClickedButton, ClickedButton> Help::execute(sf::RenderWindow* window)
{

	
	auto& texture1 = Resources::instance().getTextures()[help1];
	auto& texture2 = Resources::instance().getTextures()[help2];
	auto& texture3 = Resources::instance().getTextures()[help3];
	auto background1 = sf::Sprite(texture1);
	auto background2 = sf::Sprite(texture2);
	auto background3 = sf::Sprite(texture3);

	//first help screen:
	auto firstMenu = Menu(window);
	firstMenu.setSprite(background1);
	firstMenu.addWithPos("Next", { 0.395 * BOARD_WIDTH, 0.726 * BOARD_HEIGHT }, std::make_unique<Next>());

	firstMenu.activate();
	
	//second help screen:
	auto secondMenu = Menu(window);
	secondMenu.setSprite(background2);
	secondMenu.addWithPos("Next", { 0.395 * BOARD_WIDTH, 0.726 * BOARD_HEIGHT }, std::make_unique<Next>());

	secondMenu.activate();

	//third help screen:
	auto thirdMenu = Menu(window);
	thirdMenu.setSprite(background3);
	thirdMenu.addWithPos("Done", { 0.395 * BOARD_WIDTH, 0.726 * BOARD_HEIGHT }, std::make_unique<Next>());

	thirdMenu.activate();
	return { ClickedButton::Invalid, ClickedButton::Invalid };
}