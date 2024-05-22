#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"



// ===== consts: ==========
const b2Vec2 jumpImpulse(0.0f, -10.0f);
const float SCALE = 30.0f;

const int GUN_BULLET_DAMAGE = 60;
const int SNIPER_BULLET_DAMAGE = 40;
const int GHOST_DAMAGE = 40;
const int BAT_DAMAGE = 30;
const int SPIDER_DAMAGE = 180;
const int THORNS_DAMAGE = 60;

const int PLAYER_HEALTH = 180;
const int BAT_HEALTH = 50;
const int SPIDER_HEALTH = 140;
const int GHOST_HEALTH = 70;

const int HEART_HEALING = 30;


const int TILE_SIZE = 40;
constexpr int BOARD_WIDTH = 1450;
constexpr int BOARD_HEIGHT = 950;
// ===== enums: ==========
enum ObjectTypes
{
	wallObject = '#',
	firstPlayerObject = 'P',
	secondPlayerObject = 'p',
	enemySpiderObject = '&',
	GhostObject = 'g',
	heartObject = 'H',
	coinObject = 'C',
	batObject = 'Q',
	gunObject = 'G',
	sniperObject = 'S',
	thronsObject = 't',
	fullHeartObject = 'h',
	fireObject = 'F',
	healingBallObject = '0',
	ghostHouseObject = 'W',
	batsHouseObject = 'E'

};
//    --------------
enum TextureTypes
{
	wall,
	firstPlayer,
	secondPlayer,
	enemy,
	menuBackGround,
	templeBackground,
	enemySpider,
	enemyGhost,
	heart,
	coin,
	enemyBat,
	gun,
	sniper,
	coins,
	gunBullet,
	sniperBullet,
	throns,
	fire,
	healingBall,
	ghostHouse,
	batsHouse,
	help1,
	help2,
	help3,
	win,
	lose,
	winGame
};


enum class ClickedButton
{
	StartGame,
	Help,
	Exit,
	SinglePlayer,
	MultiPlayer,
	Back,
	Next,
	FriendlyFireON,
	FriendlyFireOFF,
	Invalid
};
enum SoundTypes
{
	background,
	casinoReward,
	coinTaken,
	decreaseHealth,
	explosionGun,
	fight,
	gameShot,
	handgunRelease,
	handgunTaken,
	hitByBullet,
	increaseHealth,
	levelLost,
	menuClick,
	playerJumping,
	playerLosing,
	changeWeapon,
	fireSound,
	healSound,
	won,
	newlvl

};








//    --------------
//enum class GameObjectIndex
//{
//	firstPlayer,
//	secondPlayer,
//	Wall,
//	MAX
//};
//    --------------
enum class Direction
{
	Up,
	Down,
	Right,
	Left,
	Stay,
	Max,
};
//    --------------
