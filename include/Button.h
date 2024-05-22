#pragma once


//includes:
#include "io.h"

class Button
{
public:
    //Constructors:
    Button();
    Button(std::string text, sf::Vector2f shapeSize, int textSize, sf::Color bgcolor, sf::Color textColor
        , sf::Vector2f pos, const sf::Font& font);

    //set indviduals:
    void setFont(const sf::Font& font);
    void setBold();
    void setBackColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPosition(sf::Vector2f pos);

    //reset the button info:
    void setButtonInfo(std::string text, sf::Vector2f size, int charSize, sf::Color bgcolor,
        sf::Color textColor, sf::Vector2f pos, const sf::Font& font);

    //get individuals:
    sf::RectangleShape getbuttonBg() const;
    sf::Text getext() const;


    //draw function:
    void drawTo(sf::RenderWindow& window);

    bool isMouseOver(sf::RenderWindow& window);

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
};