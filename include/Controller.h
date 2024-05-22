#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include "io.h"
#include "FirstPlayer.h"
#include <iostream>
#include "Board.h"
#include "Resources.h"
#include "Menu.h"
#include "Command.h"
#include "StartGame.h"
#include "Help.h"
#include "Exit.h"
class Board;


class Controller
{

public:
    Controller();
    ~Controller();
    void run();
    void startGame();
    void handleEvent(sf::Event& event1, sf::Event& event2, Board& gameBoard);

private:
    //window:
    sf::RenderWindow* m_window;
    Menu m_mainMenu;
    
    sf::Clock gameClock = sf::Clock();
    // hon fe t3deel


    bool m_isMultiplyer = false;
    bool m_isFriendlyOn = false;

    sf::Keyboard::Key keyToEvent(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyRight, sf::Keyboard::Key keyLeft, sf::Keyboard::Key keyDown);
    bool m_changeFirstWeapon, m_changeSecondWeapon;
    bool m_firstPlayerShoot, m_secondPlayerShoot;

    sf::Clock m_firstBulletTimer, m_secondBulletTimer;

};