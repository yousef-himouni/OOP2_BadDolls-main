#include "Menu.h"

Menu::Menu()
{
	auto& texture = Resources::instance().getTextures()[menuBackGround];
	m_bgSprite = sf::Sprite(texture);
	m_bgSprite.setColor(sf::Color(255, 255, 255, 75));
}

Menu::Menu(sf::RenderWindow* window) : m_window(window)
{
	auto& texture = Resources::instance().getTextures()[menuBackGround];
	m_bgSprite = sf::Sprite(texture);
	m_bgSprite.setColor(sf::Color(255, 255, 255, 75));
}
//-------------------------------------------------------------------------------------------
void Menu::add(std::string buttonName, std::unique_ptr<Command> c)
{
	auto temp = Button(buttonName,
		{ static_cast<float>(0.2 * BOARD_WIDTH), static_cast<float>(0.12 * BOARD_HEIGHT) },
		static_cast<int>(0.05 * BOARD_HEIGHT),
		sf::Color::Transparent,
		sf::Color::Yellow,
		{ static_cast<float>(0.4 * BOARD_WIDTH), static_cast<float>((0.2 + m_options.size() * 0.2) * BOARD_HEIGHT) },
		m_font);


	m_options.emplace_back(option(temp, std::move(c)));
}
//-------------------------------------------------------------------------------------------
void Menu::addWithPos(std::string buttonName, sf::Vector2f pos, std::unique_ptr<Command> c)
{
	auto temp = Button(buttonName,
		{ static_cast<float>(0.2 * BOARD_WIDTH), static_cast<float>(0.12 * BOARD_HEIGHT) },
		static_cast<int>(0.05 * BOARD_HEIGHT),
		sf::Color::Transparent,
		sf::Color::Yellow,
		pos,m_font);


	m_options.emplace_back(option(temp, std::move(c)));
}
//-------------------------------------------------------------------------------------------
std::pair<ClickedButton, ClickedButton> Menu::activate()
{
	//first = sigle/multiple mode , second = firefriendly is ON/OFF:
	auto choices = std::pair<ClickedButton, ClickedButton>(ClickedButton::Invalid, ClickedButton::Invalid);
	//presenting the diffuclty screen:
	while (m_window->isOpen())
	{
		//clearing the window
		m_window->clear();

		// Draw buttons
		m_window->draw(m_bgSprite);
		for (auto& option : m_options)
		{
			option.first.drawTo(*m_window);
		}

		//Display:
		m_window->display();


		if (auto event = sf::Event{}; m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window->close();
				delete m_window;
				exit(EXIT_SUCCESS);
				break;

			case sf::Event::MouseButtonReleased:
				choices = handleClick(event.mouseButton, m_window);
				if (choices.first != ClickedButton::Invalid)
					return choices;
				break;
			//mouse houvering over buttons:
			case sf::Event::MouseMoved:
				handleHoverOver(m_window);
				break;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------
std::pair<ClickedButton, ClickedButton> Menu::handleClick(const sf::Event::MouseButtonEvent& event, sf::RenderWindow* window)
{

	for (auto& option : m_options)
	{
		Resources::instance().playSound(menuClick);
		if (option.first.getbuttonBg().getGlobalBounds().contains(
			window->mapPixelToCoords({ event.x, event.y })))
		{
			return option.second->execute(window);
		}
	}
	return { ClickedButton::Invalid, ClickedButton::Invalid };
}
//-------------------------------------------------------------------------------------------
void Menu::handleHoverOver(sf::RenderWindow* window)
{
	for (auto& option : m_options)
	{
		//if the user hovered over one of the options then change color:
		if (option.first.isMouseOver(*window))
			option.first.setTextColor(sf::Color::Blue);
		else
			option.first.setTextColor(sf::Color::Yellow);
	}
}
//-------------------------------------------------------------------------------------------
void Menu::setFriendlyFireMode(ClickedButton mode)
{
	m_fireFMode = mode;
}
//-------------------------------------------------------------------------------------------
void Menu::setPlayerMode(ClickedButton mode)
{
	m_sigleMultipleMode = mode;
}
//-------------------------------------------------------------------------------------------
ClickedButton Menu::getFriendlyFireMode() const
{
	return m_fireFMode;
}
//-------------------------------------------------------------------------------------------
ClickedButton Menu::getPlayerMode() const
{
	return m_sigleMultipleMode;
}
//-------------------------------------------------------------------------------------------
void Menu::setWindow(sf::RenderWindow* window)
{
	m_window = window;
}
//-------------------------------------------------------------------------------------------
void Menu::setSprite(sf::Sprite newSprite)
{
	m_bgSprite = newSprite;
}