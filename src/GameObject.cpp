#include "GameObject.h"

GameObject::GameObject(const sf::Sprite& sprite): m_sprite(sprite){}
//-------------------------------------------------------------------------------------------
//return the sprite:
sf::Sprite& GameObject::getSprite() 
{
    return m_sprite;
}
//-------------------------------------------------------------------------------------------
//set sprite:
void GameObject::setSprite(sf::Sprite sprite)
{
    m_sprite = sprite;
}
//-------------------------------------------------------------------------------------------
//get sprite position:
sf::Vector2f GameObject::getPosition() const
{
    return m_sprite.getPosition();
}
//-------------------------------------------------------------------------------------------
//set sprite position:
void GameObject::setPosition(sf::Vector2f position)
{
    m_sprite.setPosition(position);
}
//-------------------------------------------------------------------------------------------
//draw object to the window:
void GameObject::draw(sf::RenderWindow* window)
{
    window->draw(m_sprite);
}
//-------------------------------------------------------------------------------------------
//set the previouse position:
void GameObject::setPrevPosition(sf::Vector2f pos)
{
    m_prevPosition = pos;
}
//-------------------------------------------------------------------------------------------
//get the previouse position:
sf::Vector2f GameObject::getPrevPosition() const
{
    return m_prevPosition;
}
//-------------------------------------------------------------------------------------------
b2Body* GameObject::getB2DBody()
{
    return m_b2dBody;
}
//-------------------------------------------------------------------------------------------
void GameObject::setLvlSize(sf::Vector2f newLvl)
{
    m_boardLvlSize = newLvl;
}
//-------------------------------------------------------------------------------------------
sf::Vector2f GameObject::getLvlSize() const
{
    return m_boardLvlSize;
}
//-------------------------------------------------------------------------------------------
//function that sets the sprite origin:
void GameObject::setSpriteOrigin(sf::Vector2f newOrigin)
{
    m_sprite.setOrigin(newOrigin);
}
//-------------------------------------------------------------------------------------------
//function that sets the sprite scale:
void GameObject::setSpriteScale(sf::Vector2f newScale)
{
    m_sprite.setScale(newScale);
}
//-------------------------------------------------------------------------------------------
//function that returns the sprite height:
float GameObject::getSpriteHeight() const
{
    return m_sprite.getGlobalBounds().height;
}
//-------------------------------------------------------------------------------------------
//function that returns the sprite width:
float GameObject::getSpriteWidth() const
{
    return m_sprite.getGlobalBounds().width;
}
//-------------------------------------------------------------------------------------------
//function that moves the sprite:
void GameObject::moveSprite(sf::Vector2f offset)
{
    m_sprite.move(offset);
}
//-------------------------------------------------------------------------------------------
//function that returns the global bounds of the sprite:
sf::FloatRect GameObject::getSpriteBounds() const
{
    return m_sprite.getGlobalBounds();
}
//-------------------------------------------------------------------------------------------
//function that sets the sprite position:
void GameObject::setSpritePosition(sf::Vector2f newPosition)
{
    m_sprite.setPosition(newPosition);
}