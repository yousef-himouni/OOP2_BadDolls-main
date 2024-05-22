#include "Controller.h"

//default Controller constructor:

Controller::Controller() : m_changeFirstWeapon(false), m_changeSecondWeapon(false),
m_firstPlayerShoot(false), m_secondPlayerShoot(false), m_isMultiplyer(false), m_isFriendlyOn(false)
{

	m_window = new sf::RenderWindow(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Bad Dolls");
	// Create the main menu
	m_mainMenu.setWindow(m_window);

	// Add options to the main menu
	m_mainMenu.add("Start Game", std::make_unique<StartGame>());
	m_mainMenu.add("Help", std::make_unique<Help>());
	m_mainMenu.add("Exit", std::make_unique<Exit>());

	m_firstBulletTimer.restart();
	m_secondBulletTimer.restart();
}
//Destructor:
Controller::~Controller()
{
	delete m_window;
	m_window = nullptr;
}
//-------------------------------------------------------------------------------------------
//function that runs the game from start to end:
void Controller::run()
{
	Resources::instance().playMusic();
	m_window->setFramerateLimit(60);



	// Display the MainMenu and start if the player clicks start game:
	startGame();
}
//-------------------------------------------------------------------------------------------
void Controller::startGame()
{
	srand(static_cast<unsigned>(time(nullptr)));
	// Outer loop to allow for showing the main menu again if player chooses
	// to return to main menu after winning or losing a level.
	while (true)
	{
		// Main Menu
		while (true)
		{
			auto choices = m_mainMenu.activate();

			if (choices.first == ClickedButton::Back)
			{
				continue; // If 'Back' is chosen, display main menu again
			}

			if (choices.first == ClickedButton::MultiPlayer)
			{
				m_isMultiplyer = true;
			}

			if (choices.second == ClickedButton::FriendlyFireON)
			{
				m_isFriendlyOn = true;
			}

			break; // Exit the loop if choices.first is not 'Back'
		}

		Resources::instance().setSinglePlayerMode(!m_isMultiplyer);
		Resources::instance().setFriendlyFire(m_isFriendlyOn);



		sf::Event event1;
		sf::Event event2;

		while (!Resources::instance().getGameFinished())
		{
			ContactListener listener;
			Board gameBoard(m_window, Resources::instance().getCurrentLevel(), listener);
			while (m_window->isOpen() && !Resources::instance().getLevelWon() && !Resources::instance().getLevelLost())
			{
				// Clear the window:
				m_window->clear(sf::Color::Black);
				// Draw the board:
				gameBoard.draw(m_window);
				// Display:
				m_window->display();

				event2.key.code = sf::Keyboard::Space;
				event1.key.code = sf::Keyboard::H;

				while (m_window->pollEvent(event1))
				{
					handleEvent(event1, event2, gameBoard);
				}

				const auto delta = gameClock.restart();
				// Get the new position
				gameBoard.updateMoving(delta);

				// Update various game elements
				gameBoard.updateBullets(delta);
				gameBoard.updateStatics(delta);
				gameBoard.updateWeapons();
				gameBoard.updateJumpStatus();

				gameBoard.stepWorld();
			}
			// If Level won
			if (Resources::instance().getLevelWon())
			{
				Resources::instance().addCurrentLevel();
				Resources::instance().resetCoins();

				if (!Resources::instance().getGameFinished())
				{

					// Winning menu:
					Resources::instance().playSound(newlvl);
					auto& winTexture = Resources::instance().getTextures()[win];
					auto winSprite = sf::Sprite(winTexture);
					auto WinMenu = Menu(m_window);
					WinMenu.setSprite(winSprite);

					WinMenu.addWithPos("Next Level", { 0.4 * BOARD_WIDTH, 0.6 * BOARD_HEIGHT }, std::make_unique<Next>());
					WinMenu.addWithPos("Back To Main Menu", { 0.4 * BOARD_WIDTH, 0.8 * BOARD_HEIGHT }, std::make_unique<Back>());

					auto choice = WinMenu.activate();
					if (choice.first == ClickedButton::Next)
					{
						continue; // Break out of the inner loop to restart the game
					}
					else if (choice.first == ClickedButton::Back)
					{
						// If 'Back To Main Menu' is chosen, break out of this loop
						// which will cause the outer loop to show the main menu again.
						break;
					}
				}

			}
			else if (Resources::instance().getLevelLost()) // If Level lost
			{
				Resources::instance().resetCoins();
				Resources::instance().playSound(levelLost);
				// losing menu:
				auto& loseTexture = Resources::instance().getTextures()[lose];
				auto loseSprite = sf::Sprite(loseTexture);
				auto loseMenu = Menu(m_window);
				loseMenu.setSprite(loseSprite);


				loseMenu.addWithPos("Back To Main Menu", { 0.39 * BOARD_WIDTH, 0.7 * BOARD_HEIGHT }, std::make_unique<Back>());

				auto choice = loseMenu.activate();
				if (choice.first == ClickedButton::Back)
				{
					// If 'Back To Main Menu' is chosen, break out of this loop
					// which will cause the outer loop to show the main menu again.
					break;
				}
			}
		}

		// If all the rounds are won
		if (Resources::instance().getGameFinished())
		{
			Resources::instance().playSound(won);
			Resources::instance().resetGame();
			// Winning menu:
			auto& winTexture = Resources::instance().getTextures()[win];
			auto winSprite = sf::Sprite(winTexture);
			auto WinMenu = Menu(m_window);
			WinMenu.setSprite(winSprite);

			WinMenu.addWithPos("Back To Main Menu", { 0.4 * BOARD_WIDTH, 0.6 * BOARD_HEIGHT }, std::make_unique<Back>());
			WinMenu.addWithPos("Exit Game", { 0.4 * BOARD_WIDTH, 0.8 * BOARD_HEIGHT }, std::make_unique<Exit>());

			auto choice = WinMenu.activate();

			if (choice.first == ClickedButton::Back)
			{
				// If 'Back To Main Menu' is chosen, the outer loop will show the main menu again.
				continue;
			}
			else if (choice.first == ClickedButton::Exit)
			{
				// If 'Exit Game' is chosen, exit the function which will ultimately close the game.
				return;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
void Controller::handleEvent(sf::Event& event1, sf::Event& event2, Board& gameBoard)
{
	if (event1.type == sf::Event::Closed || event2.type == sf::Event::Closed)
	{
		m_window->close();
		delete m_window;
		exit(EXIT_SUCCESS);
	}

	event1.key.code = keyToEvent(sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Down);
	event2.key.code = keyToEvent(sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::S);

	m_changeFirstWeapon = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	m_changeSecondWeapon = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	if (m_firstBulletTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		m_firstPlayerShoot = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
		m_firstBulletTimer.restart();
	}
	if (m_secondBulletTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		m_secondPlayerShoot = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
		m_secondBulletTimer.restart();
	}


	gameBoard.changeWeapon(m_changeFirstWeapon, m_changeSecondWeapon);
	gameBoard.directionPlayers(event1.key.code, event2.key.code);
	gameBoard.shoot(m_firstPlayerShoot, m_secondPlayerShoot);

	m_changeFirstWeapon = false;
	m_changeSecondWeapon = false;
	m_firstPlayerShoot = false;
	m_secondPlayerShoot = false;
}
//-------------------------------------------------------------------------------------------
sf::Keyboard::Key Controller::keyToEvent(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyRight, sf::Keyboard::Key keyLeft, sf::Keyboard::Key keyDown)
{
	if (sf::Keyboard::isKeyPressed(keyUp))
	{
		return sf::Keyboard::Up;
	}
	else if (sf::Keyboard::isKeyPressed(keyRight))
	{
		return sf::Keyboard::Right;
	}
	else if (sf::Keyboard::isKeyPressed(keyLeft))
	{
		return sf::Keyboard::Left;
	}
	else if (sf::Keyboard::isKeyPressed(keyDown))
	{
		return sf::Keyboard::Down;
	}

	return sf::Keyboard::Unknown;
}
