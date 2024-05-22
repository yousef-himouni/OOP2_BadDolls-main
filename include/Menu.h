#pragma once

#include "Command.h"
#include "Button.h"
#include "Resources.h"
#include <memory>


class Menu
{
public:
	Menu();
	Menu(sf::RenderWindow* window);
	~Menu() {}
	void add(std::string buttonName, std::unique_ptr<Command> c);
	void addWithPos(std::string buttonName, sf::Vector2f pos, std::unique_ptr<Command> c);
	std::pair<ClickedButton, ClickedButton> activate();
	void setWindow(sf::RenderWindow* window);
	void setFriendlyFireMode(ClickedButton mode);
	void setPlayerMode(ClickedButton mode);
	ClickedButton getFriendlyFireMode() const;
	ClickedButton getPlayerMode() const;
	void setSprite(sf::Sprite newSprite);


private:

	//background sprite:
	sf::Sprite m_bgSprite;

	sf::Font m_font = Resources::instance().getFont();
	sf::RenderWindow* m_window;

	ClickedButton m_fireFMode;
	ClickedButton m_sigleMultipleMode;


	typedef std::pair<Button, std::unique_ptr<Command>> option;
	std::vector<option> m_options;
	

	void handleHoverOver(sf::RenderWindow* window);
	std::pair<ClickedButton, ClickedButton> handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window);
};