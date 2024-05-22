#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include<iostream>
#include<fstream>
#include<SFML/Audio.hpp>
#include "AnimationData.h"

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)


//singleton

class Resources
{
private:
	std::vector<std::string> m_singlePlayerLevels;
	std::vector<std::string> m_multiPlayerLevels;
	std::vector<sf::Texture> m_textures;
	std::vector<sf::Sound> m_sounds;
	std::vector<sf::SoundBuffer> m_buffers;
	std::vector<AnimationData> m_animationData;
	sf::Texture m_texture;
	sf::Font m_font;
	bool m_friendlyFire;

	int m_levelCoins;
	int m_takenCoins;
	bool m_levelWon;
	int m_currentLevel;

	int m_numOfPlayers;

	bool m_singlePlayerMode;
	Resources();
	Resources(const Resources&) = delete;
	Resources& operator = (const Resources&) = delete;

	
	std::vector<std::string> readNamesVector(const char[]) const;
	std::vector<sf::Texture> getTexturesVector(const std::vector<std::string>&)const;
	std::vector<sf::Sound> fillSoundsVector(const std::vector<sf::SoundBuffer>& buffer)const;
	std::vector<sf::SoundBuffer> fillBufferVector(const std::vector<std::string>&)const;
	

public:
	enum Objects
	{
		FirstPlayer,
		SecondPlayer,
		EnemySpider,
		EnemyGhost,
		Heart,
		Coin,
		EnemyBat,
		FullHeart,
		Fire,
		HealingBall,
		Max
	};
	void playMusic();
	void playSound( const int index);
	static Resources& instance();
	~Resources() = default;
	
	const std::vector<sf::Texture>& getTextures() const;
	const sf::Font& getFont() const;
	const std::string& getSingleLevel(const int index) const;
	const std::string& getMultiLevel(const int index) const;

	std::vector<std::string>buildMap(const int);
	const AnimationData& animationData(Objects object) { return m_animationData[object]; }

	void setFriendlyFire(bool f);
	bool getFriendlyFire()const;

	void addTakenCoins();
	void addLevelCoins();
	void addCurrentLevel();
	int getCurrentLevel()const;

	int getTakenCoins()const;
	int getLevelCoins()const;

	bool getLevelWon()const;
	bool getGameFinished()const;

	void setSinglePlayerMode(bool b);
	bool getSinglePlayerMode()const;

	void playerKilled();

	bool getLevelLost()const;
	void resetGame();
	void resetCoins();
	int getSingleLvlCount() const;
	int getMultipleLvlCount() const;
};