#include "Button.h"

// default empty constructor
Button::Button() {}
//-------------------------------------------------------------------------------------------
//constructor that takes as input, text, shape size, text size, background color, and text color.
// and sets the m_text and the m_shape accordingly:
Button::Button(std::string text, sf::Vector2f shapeSize, int textSize, sf::Color bgcolor, sf::Color textColor
    , sf::Vector2f pos, const sf::Font& font)
{
    m_text.setString(text);
    m_text.setFillColor(textColor);
    m_text.setCharacterSize(textSize);
    m_text.setFont(font);
    m_shape.setSize(shapeSize);
    m_shape.setFillColor(bgcolor);
    setPosition(pos);
}
//-------------------------------------------------------------------------------------------
//set function that sets all the shape and text details:
void Button::setButtonInfo(std::string text, sf::Vector2f shapeSize, int textSize, sf::Color bgcolor,
    sf::Color textColor, sf::Vector2f pos, const sf::Font& font)
{
    m_text.setString(text);
    m_text.setFillColor(textColor);
    m_text.setCharacterSize(textSize);
    m_text.setFont(font);
    m_shape.setSize(shapeSize);
    m_shape.setFillColor(bgcolor);
    setPosition(pos);
}
//-------------------------------------------------------------------------------------------
//function that sets the font of the text:
void Button::setFont(const sf::Font& font)
{
    m_text.setFont(font);
}
//-------------------------------------------------------------------------------------------
//function that sets the text to bold:
void Button::setBold()
{
    m_text.setStyle(sf::Text::Bold);
}
//-------------------------------------------------------------------------------------------
//function that sets the shape color:
void Button::setBackColor(sf::Color color)
{
    m_shape.setFillColor(color);
}
//-------------------------------------------------------------------------------------------
//function that sets the text color:
void Button::setTextColor(sf::Color color)
{
    m_text.setFillColor(color);
}
//-------------------------------------------------------------------------------------------
//function that sets the shape and the text positions:
void Button::setPosition(sf::Vector2f pos)
{
    //set the button position:
    m_shape.setPosition(pos);
    //set the text position to be in the center of the button:
    m_text.setPosition(pos.x + (m_shape.getGlobalBounds().width - m_text.getGlobalBounds().width) / 2,
        pos.y + (m_shape.getGlobalBounds().height / 2 - m_text.getGlobalBounds().height / 2));
}
//-------------------------------------------------------------------------------------------
//get function that returs the background of the button:
sf::RectangleShape Button::getbuttonBg() const
{
    return m_shape;
}
//-------------------------------------------------------------------------------------------
//get function that returns the text:
sf::Text Button::getext() const
{
    return m_text;
}
//-------------------------------------------------------------------------------------------
//function that draws the rectangle background and the text to the window:
void Button::drawTo(sf::RenderWindow& window)
{
    window.draw(m_shape);
    window.draw(m_text);
}
//-------------------------------------------------------------------------------------------
//this function checks if the mouse is over the button(rect and text):
bool Button::isMouseOver(sf::RenderWindow& window) {

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    // Check if the mouse is over the image
    if (m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
        return true;
    else
        return false;
}
//-------------------------------------------------------------------------------------------