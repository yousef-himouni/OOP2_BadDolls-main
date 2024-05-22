#include "Board.h"


//board constructor:
Board::Board(const sf::RenderWindow* window, const int lvl, ContactListener& listener) : m_world(std::make_unique<b2World>(b2Vec2(0, 9.8))), m_batHouseExists(false),
m_ghostHouseExists(false)
{
	m_creatingBatsTimer.restart();
	m_creatingGhostsTimer.restart();
	m_world->SetContactListener(&listener);
	m_backGround.setTexture(Resources::instance().getTextures()[templeBackground]);
	m_ghost.setTexture(Resources::instance().getTextures()[enemyGhost]);
	m_ghost.setTexture(Resources::instance().getTextures()[enemyBat]);
	//build the level
	auto map = Resources::instance().buildMap(lvl);//get the map text
	int numOfCols = (int)map[0].size();
	int numOfRows = (int)map.size();

	m_levelSize = sf::Vector2f((float)numOfCols * TILE_SIZE, (float)numOfRows * TILE_SIZE);

	//the level position in the center of the window
	m_levelPosition = sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f);

	//the board of the game is a rectangleShape
	m_board = sf::RectangleShape(m_levelSize);

	//make the board half transparent
	m_board.setFillColor(sf::Color(255, 255, 255, 128));

	//the origin of the board in the center of the level
	m_board.setOrigin(m_levelSize / 2.f);

	m_board.setPosition(m_levelPosition);

	m_gunBulletSprite.setTexture(Resources::instance().getTextures()[gunBullet]);
	m_sniperBulletSprite.setTexture(Resources::instance().getTextures()[sniperBullet]);

	//build the ibjects from the text file (the level file)
	for (int row = 0; row < numOfRows; row++)
	{
		for (int col = 0; col < numOfCols; col++)
		{
			char tile = map[row][col];

			if (tile == coinObject)
			{
				Resources::instance().addLevelCoins();
			}
			else if (tile == ghostHouseObject)
			{
				m_ghostHouseExists = true;
				m_ghostsHousePos = sf::Vector2f(Xposition(col), Yposition(row));
			}
			else if (tile == batsHouseObject)
			{
				m_batHouseExists = true;
				m_batsHousePos = sf::Vector2f(Xposition(col), Yposition(row));
			}
			makeObject((ObjectTypes)tile, sf::Vector2f(Xposition(col), Yposition(row)), m_world.get());

		}
	}
}
//-------------------------------------------------------------------------------------------
//function that draws the board objects on the window:
void Board::draw(sf::RenderWindow* window)
{

	window->draw(m_backGround);
	drawInfo(window);
	window->draw(m_board);

	//draw the moving objects with the health bar for each one
	for (size_t i = 0; i < m_movingObjects.size(); i++)
	{
		m_healthBars[i].setPosition(m_movingObjects[i]->getPosition());
		m_movingObjects[i]->draw(window);
		m_healthBars[i].drawHealthBar(window);
	}

	//draw the chosen weapon for each player
	for (auto& object : m_movingObjects)
	{
		Player* player = dynamic_cast<Player*>(object.get());
		if (player)
		{
			for (int i = 0; i < player->getWeaponCount(); i++)
			{
				Weapon weapon = player->getWeapon(i);
				if (weapon.getChosen())
				{
					weapon.setPosition(sf::Vector2f(player->getPosition().x + 6, player->getPosition().y + 20));
					weapon.draw(window);
				}
			}
		}
	}

	//draw the static objects
	for (auto& object : m_staticObjects)
	{
		object->draw(window);
	}
	for (auto& bullet : m_bullets)
	{
		bullet->draw(window);
	}

}

//function that draws the information about the player like points, kills, coins
void Board::drawInfo(sf::RenderWindow* window)
{
	auto font = Resources::instance().getFont();

	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f(200.0f, 70.0f));
	bar.setFillColor(sf::Color(255, 255, 255, 170));
	bar.setOutlineColor(sf::Color::Black);
	bar.setOutlineThickness(2);
	bar.setOrigin(bar.getGlobalBounds().width / 2.0f, bar.getGlobalBounds().height / 2.0f);
	bar.setPosition(window->getSize().x / 2.0f, m_board.getGlobalBounds().top - 25);

	//Coins:
	auto coinsTexture = Resources::instance().getTextures()[coins];
	auto coinsSprite = sf::Sprite(coinsTexture);

	std::string coinsString = std::to_string(Resources::instance().getTakenCoins()) + " / " + std::to_string(Resources::instance().getLevelCoins());
	auto coinText = sf::Text(coinsString, font, 20);
	coinText.setPosition(bar.getPosition().x - bar.getGlobalBounds().width / 2 + 10.0f, bar.getPosition().y);
	coinText.setFillColor(sf::Color::Black);

	coinsSprite.setPosition({ coinText.getPosition().x, coinText.getPosition().y - coinText.getGlobalBounds().height
		- 10.0f });
	
	//Level:
	std::string lvlString;
	auto caption = sf::Text("Level", font, 20);
	if (Resources::instance().getSinglePlayerMode())
	{
		 lvlString = std::to_string(Resources::instance().getCurrentLevel() + 1) + " / " + std::to_string(Resources::instance().getSingleLvlCount());
	}
	else
	{
		lvlString = std::to_string(Resources::instance().getCurrentLevel() + 1) + " / " + std::to_string(Resources::instance().getMultipleLvlCount());
	}
	
	auto lvlText = sf::Text(lvlString, font, 20);
	lvlText.setPosition(bar.getPosition().x + 40.0f , bar.getPosition().y);
	caption.setPosition(lvlText.getPosition().x, lvlText.getPosition().y - lvlText.getGlobalBounds().height - 10.0f);
	lvlText.setFillColor(sf::Color::Black);
	caption.setFillColor(sf::Color::Black);

	window->draw(bar);
	window->draw(coinText);
	window->draw(lvlText);
	window->draw(caption);
	window->draw(coinsSprite);
}
//-------------------------------------------------------------------------------------------
//function that updates the players movements and call the collision handling:
void Board::updateMoving(sf::Time delta)
{
	for (auto& moving : m_movingObjects)
	{
		if (moving)
		{
			MovingObject* ob = moving.get();

			if (Enemy* enemy = dynamic_cast<Enemy*>(ob))
			{
				if (EnemyBat* bat = dynamic_cast<EnemyBat*>(enemy))
				{
					bat->setFirstPlayerPosition(findFirstPlayer());
					bat->setSecondPlayerPosition(findSecondPlayer());
					bat->update(delta);
				}
				else if (EnemyGhost* ghost = dynamic_cast<EnemyGhost*>(enemy))
				{
					ghost->setFirstPlayerPosition(findFirstPlayer());
					ghost->setSecondPlayerPosition(findSecondPlayer());
					ghost->update(delta);
				}
				else if (EnemySpider* Spider = dynamic_cast<EnemySpider*>(enemy))

				{
					Spider->update(delta);
				}
			}
			else
			{
				moving->update(delta);
			}

		}
	}
	collision();
}

//-------------------------------------------------------------------------------------------
//update the static objects that have animation
void Board::updateStatics(sf::Time delta)
{
	for (auto& object : m_staticObjects)
	{
		StaticObject* ob = object.get();
		Heart* heart = dynamic_cast<Heart*>(ob);
		if (heart)
		{
			heart->update(delta);
		}
		else if (Coin* coin = dynamic_cast<Coin*>(ob))
		{
			coin->update(delta);
		}
		else if (Fire* fire = dynamic_cast<Fire*>(ob))
		{
			fire->update(delta);
		}
		else if (HealingBall* healing = dynamic_cast<HealingBall*>(ob))
		{
			healing->update(delta);
		}


	}
}
//------------------------------------------------------------------------------------------
//function that changes the direction of the player and the guns according to the player's directoin
void Board::directionPlayers(sf::Keyboard::Key first, sf::Keyboard::Key second)
{

	for (size_t i = 0; i < m_movingObjects.size(); i++)
	{
		MovingObject* ob = m_movingObjects[i].get();

		Player* playerObject = dynamic_cast<Player*>(ob);
		if (playerObject)
		{
			//change first player direction and his weapon
			if (FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(playerObject))
			{
				firstPlayerObject->direction(first);
				for (rsize_t j = 0; j < firstPlayerObject->getWeaponCount(); j++)
				{
					firstPlayerObject->getWeapon(j).setWeaponDir(firstPlayerObject->getDirection());
				}


			}
			//change second player direction and his weapon
			else if (SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(playerObject))
			{
				secondPlayerObject->direction(second);
				for (rsize_t j = 0; j < secondPlayerObject->getWeaponCount(); j++)
				{
					secondPlayerObject->getWeapon(j).setWeaponDir(secondPlayerObject->getDirection());

				}
			}
		}
	}
}

void Board::updateBullets(sf::Time delta)
{
	for (auto& bullet : m_bullets)
	{
		Bullet* ob = bullet.get();
		GunBullet* gunBulletObject = dynamic_cast<GunBullet*>(ob);
		if (gunBulletObject)
		{
			gunBulletObject->updateBullet(delta.asSeconds());
		}

		else if (SniperBullet* sniperBulletObject = dynamic_cast<SniperBullet*>(ob))
		{
			sniperBulletObject->updateBullet(2 * delta.asSeconds());
		}
	}
}
void Board::updateWeapons()
{
	for (auto& object : m_movingObjects)
	{
		if (Player* playerObject = dynamic_cast<Player*>(object.get()))
		{
			if (FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(playerObject))
			{
				if (firstPlayerObject->getDirection() == Direction::Left || firstPlayerObject->getDirection() == Direction::Right)
				{
					firstPlayerObject->changeWeaponDirection(firstPlayerObject->getDirection() == Direction::Left ? sf::Keyboard::Left : sf::Keyboard::Right);
				}
			}
			else if (SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(playerObject))
			{
				if (secondPlayerObject->getDirection() == Direction::Left || secondPlayerObject->getDirection() == Direction::Right)
				{
					secondPlayerObject->changeWeaponDirection(secondPlayerObject->getDirection() == Direction::Left ? sf::Keyboard::Left : sf::Keyboard::Right);
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------
void Board::updateJumpStatus()
{
	for (auto& object : m_movingObjects)
	{
		MovingObject* ob = object.get();

		FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(ob);
		if (firstPlayerObject)
		{
			firstPlayerObject->updateJumpStatus();
		}

		SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(ob);
		if (secondPlayerObject)
		{
			secondPlayerObject->updateJumpStatus();
		}
	}
}
//-------------------------------------------------------------------------------------------
//function that changes the weapon of each player
void Board::changeWeapon(bool first, bool second)
{
	for (auto& object : m_movingObjects)
	{
		MovingObject* ob = object.get();

		FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(ob);
		if (firstPlayerObject && first)
		{
			for (size_t i = 0; i < firstPlayerObject->getWeaponCount(); i++)
			{
				if (firstPlayerObject->getWeapon(i).getChosen())
				{
					Resources::instance().playSound(SoundTypes::changeWeapon);
					firstPlayerObject->getWeapon(i).setChosen(false);
					firstPlayerObject->getBullet(i).setChosen(false);
					firstPlayerObject->getWeapon((i + 1) % firstPlayerObject->getWeaponCount()).setChosen(true);
					firstPlayerObject->getBullet((i + 1) % firstPlayerObject->getWeaponCount()).setChosen(true);
					break;
				}
			}
		}

		SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(ob);
		if (secondPlayerObject && second)
		{
			for (size_t i = 0; i < secondPlayerObject->getWeaponCount(); i++)
			{
				if (secondPlayerObject->getWeapon(i).getChosen())
				{
					Resources::instance().playSound(SoundTypes::changeWeapon);
					secondPlayerObject->getWeapon(i).setChosen(false);
					secondPlayerObject->getBullet(i).setChosen(false);
					secondPlayerObject->getWeapon((i + 1) % secondPlayerObject->getWeaponCount()).setChosen(true);
					secondPlayerObject->getBullet((i + 1) % secondPlayerObject->getWeaponCount()).setChosen(true);
					break;
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------
// function that check the collesion between all the objects in the board:
void Board::collision()
{
	// Check collisions between moving objects and static objects:
	for (const auto& movingObject : m_movingObjects)
	{
		for (const auto& staticObject : m_staticObjects)
		{
			if (collide(*movingObject, *staticObject))
			{
				CollisionHandling::instance().handleCollision(*movingObject, *staticObject);
			}
		}
	}

	for (const auto& movingObject : m_movingObjects)
	{
		for (const auto& bulletObject : m_bullets)
		{
			if (collide(*movingObject, *bulletObject))
			{
				CollisionHandling::instance().handleCollision(*movingObject, *bulletObject);
			}
		}
	}

	for (const auto& staticObject : m_staticObjects)
	{
		for (const auto& bulletObject : m_bullets)
		{
			if (collide(*staticObject, *bulletObject))
			{
				CollisionHandling::instance().handleCollision(*staticObject, *bulletObject);
			}
		}
	}

	// Check collisions between moving objects and other moving objects:
	for_each_pair(m_movingObjects.begin(), m_movingObjects.end(), [this](auto& a, auto& b)
		{
			if (collide(*a, *b)) {
				CollisionHandling::instance().handleCollision(*a, *b);
			}
		}
	);


	handleBoard();
}
//-------------------------------------------------------------------------------------------
//check if two objects intersects:
bool Board::collide(GameObject& a, GameObject& b)
{
	return a.getSpriteBounds().intersects(b.getSpriteBounds());
}
//-------------------------------------------------------------------------------------------
//function that deletes objects from the board
void Board::handleBoard()
{
	//delete from static objects
	std::erase_if(m_staticObjects, [](const auto& object) {return object->getDelete(); });
	std::erase_if(m_bullets, [](const auto& bullet) {return bullet->getDelete(); });
	//delete from moving objects, we used this way in deleteing here because we need to delete the health bar
	//of the dead moving objects 
	for (size_t i = 0; i < m_movingObjects.size(); i++)
	{
		if (m_movingObjects[i]->isDead())
		{
			MovingObject* ob = m_movingObjects[i].get();
			if (FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(ob))
			{
				Resources::instance().playerKilled();
				firstPlayerObject->destroyBody();
			}
			else if (SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(ob))
			{
				Resources::instance().playerKilled();
				secondPlayerObject->destroyBody();
			}
			else if (EnemyBat* bat = dynamic_cast<EnemyBat*>(ob))
			{
				createGhost(bat->getPosition());
				bat->destroyBody();
			}
			else if (EnemySpider* spider = dynamic_cast<EnemySpider*>(ob))
			{
				createGhost(spider->getPosition());
				spider->destroyBody();
			}
			else if (EnemyGhost* ghost = dynamic_cast<EnemyGhost*>(ob))
			{
				ghost->destroyBody();
			}

			if (m_movingObjects.size() > 0)
				m_movingObjects.erase(m_movingObjects.begin() + i);
			if (m_healthBars.size() > 0)
				m_healthBars.erase(m_healthBars.begin() + i);
		}
		else
		{
			//update the health bar to be with the players all the time
			m_healthBars[i].setPosition(m_movingObjects[i]->getPosition());
			m_healthBars[i].setBarWidth(float(m_movingObjects[i]->getHealth()));
		}
	}
	
	if (m_creatingGhostsTimer.getElapsedTime().asSeconds() >= 15)
	{
		if (m_ghostHouseExists)
		{
			createGhost(m_ghostsHousePos);
			m_creatingGhostsTimer.restart();
		}
	}

	if (m_creatingBatsTimer.getElapsedTime().asSeconds() >= 10)
	{
		if (m_batHouseExists)
		{
			createBat();
			m_creatingBatsTimer.restart();
		}
	}
}
	//-------------------------------------------------------------------------------------------
	//function that creates the moving objects:
	std::unique_ptr<MovingObject> Board::createMovingObject(ObjectTypes type,
		const sf::Vector2f & position,
		const std::vector<sf::Texture>&textures, b2World * world)
	{
		auto sprite = sf::Sprite();
		sprite.setPosition(position);
		switch (type)
		{
		case ObjectTypes::firstPlayerObject:
			sprite.setTexture(textures[firstPlayer]);
			return std::make_unique<FirstPlayer>(sprite, world);
		case ObjectTypes::secondPlayerObject:
			sprite.setTexture(textures[secondPlayer]);
			return std::make_unique<SecondPlayer>(sprite, world);
		case ObjectTypes::enemySpiderObject:
			sprite.setTexture(textures[enemySpider]);
			return std::make_unique<EnemySpider>(sprite, world);
		case ObjectTypes::batObject:
			sprite.setTexture(textures[enemyBat]);
			return std::make_unique<EnemyBat>(sprite, world);
		case ObjectTypes::GhostObject:
			sprite.setTexture(textures[enemyGhost]);
			return std::make_unique<EnemyGhost>(sprite, world);
		}
		return nullptr;
	}
	//-------------------------------------------------------------------------------------------
	//function that creates the static objects:
	std::unique_ptr<StaticObject> Board::createStaticObject(ObjectTypes type,
		const sf::Vector2f & position,
		const std::vector<sf::Texture>&textures, b2World * world)
	{
		auto sprite = sf::Sprite();
		sprite.setPosition(position);

		switch (type)
		{
		case ObjectTypes::wallObject:
			sprite.setTexture(textures[wall]);
			return std::make_unique<Wall>(sprite, world);
		case ObjectTypes::heartObject:
			sprite.setTexture(textures[heart]);
			return std::make_unique<Heart>(sprite);
		case ObjectTypes::coinObject:
			sprite.setTexture(textures[coin]);
			return std::make_unique<Coin>(sprite);
		case ObjectTypes::gunObject:
			sprite.setTexture(textures[gun]);
			return std::make_unique<Gun>(sprite);
		case ObjectTypes::sniperObject:
			sprite.setTexture(textures[sniper]);
			return std::make_unique<Sniper>(sprite);
		case ObjectTypes::thronsObject:
			sprite.setTexture(textures[throns]);
			return std::make_unique<Throns>(sprite);
		case ObjectTypes::fireObject:
			sprite.setTexture(textures[fire]);
			sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 15);
			return std::make_unique<Fire>(sprite);
		case ObjectTypes::healingBallObject:
			sprite.setTexture(textures[healingBall]);
			return std::make_unique<HealingBall>(sprite);
		case ObjectTypes::ghostHouseObject:
			sprite.setTexture(textures[ghostHouse]);
			sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 24);
			return std::make_unique<GhostHouse>(sprite);
		case ObjectTypes::batsHouseObject:
			sprite.setTexture(textures[batsHouse]);
			sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 20);
			return std::make_unique<BatsHouse>(sprite);
		}
		return nullptr;
	}
	void Board::createGhost(sf::Vector2f position)
	{
		m_ghost.setPosition(position);


		m_movingObjects.push_back(std::move(std::make_unique<EnemyGhost>(m_ghost, m_world.get())));
		m_healthBars.push_back(HealthBar(m_ghost.getPosition(), GHOST_HEALTH));

	}
	void Board::createBat()
	{
		m_bat.setPosition(m_batsHousePos);

		m_movingObjects.push_back(std::move(std::make_unique<EnemyBat>(m_bat, m_world.get())));
		m_healthBars.push_back(HealthBar(m_ghost.getPosition(), BAT_HEALTH));
	}

	//-------------------------------------------------------------------------------------------
	//function that makes  moving and static objects and health bars and saves them in vectors:
	void Board::makeObject(const ObjectTypes & type, const sf::Vector2f & position, b2World * world)
	{


		auto& textures = Resources::instance().getTextures();
		std::unique_ptr<StaticObject> staticObjects = createStaticObject(type, position, textures, world);
		if (staticObjects)
		{
			staticObjects->setLvlSize(m_levelSize);
			m_staticObjects.push_back(std::move(staticObjects));
			return;
		}


		std::unique_ptr<MovingObject> movingObjects = createMovingObject(type, position, textures, world);

		if (movingObjects)
		{
			m_healthBars.push_back(HealthBar(movingObjects.get()->getPosition(), float(movingObjects.get()->getHealth())));
			m_movingObjects.push_back(std::move(movingObjects));
			return;
		}
	}
	//-------------------------------------------------------------------------------------------
	//according to the board
	float Board::Xposition(const int number) const
	{
		return float((m_levelPosition.x - m_levelSize.x / 2) + number * TILE_SIZE);
	}
	//-------------------------------------------------------------------------------------------
	//according to the board
	float Board::Yposition(const int number) const
	{
		return float((m_levelPosition.y - m_levelSize.y / 2) + number * TILE_SIZE);
	}
	//-------------------------------------------------------------------------------------------
	void Board::stepWorld()
	{
		m_world->Step(1.0f / 60.0f, 6, 2);
	}


	void Board::shoot(bool first, bool second)
	{
		for (auto& object : m_movingObjects)
		{
			MovingObject* ob = object.get();

			if (first)
			{
				FirstPlayer* firstPlayerObject = dynamic_cast<FirstPlayer*>(ob);
				if (firstPlayerObject)
				{
					shootForPlayer(*firstPlayerObject);
				}
			}

			if (second)
			{
				SecondPlayer* secondPlayerObject = dynamic_cast<SecondPlayer*>(ob);
				if (secondPlayerObject)
				{
					shootForPlayer(*secondPlayerObject);

				}
			}
		}
	}

	//bug, if the player took the gun then the sniper without changing weapons, it doesnt change bullets

	void Board::shootForPlayer(Player & player)
	{
		sf::Vector2f bulletPosition;
		for (size_t i = 0; i < player.getWeaponCount(); i++)
		{
			if (player.getBullet(i).getChosen())
			{
				//the player must be on right or left to shoot, else he cant shoot
				if (player.getDirection() == Direction::Right)
					bulletPosition = sf::Vector2f(player.getPosition().x + 35, player.getPosition().y + 10);
				else if (player.getDirection() == Direction::Left)
					bulletPosition = sf::Vector2f(player.getPosition().x - 35, player.getPosition().y + 10);
				else
					return;

				if (player.getBullet(i).getBulletType() == "GunBullet")
				{
					Resources::instance().playSound(gameShot);
					m_gunBulletSprite.setPosition(bulletPosition);
					m_bullets.push_back(std::make_unique<GunBullet>(m_gunBulletSprite, player.getWeapon(i).getWeaponDir()));
					break;
				}
				else if (player.getBullet(i).getBulletType() == "SniperBullet")
				{
					Resources::instance().playSound(gameShot);
					m_sniperBulletSprite.setPosition(bulletPosition);
					m_bullets.push_back(std::make_unique<SniperBullet>(m_sniperBulletSprite, player.getWeapon(i).getWeaponDir()));
					break;
				}
			}
		}
	}
	//-------------------------------------------------------------------------------------------
	//function that runs over the m_movingObjects and returns
	//the first player position:
	b2Vec2 Board::findFirstPlayer()
	{
		for (auto& object : m_movingObjects)
		{
			Player* player = dynamic_cast<Player*>(object.get());
			if (player)
			{
				FirstPlayer* firstPlayer = dynamic_cast<FirstPlayer*>(player);
				if (firstPlayer)
					return firstPlayer->getB2dPosition();
			}
		}

		return b2Vec2(100000, 100000);
	}
	//-------------------------------------------------------------------------------------------
	b2Vec2 Board::findSecondPlayer()
	{
		for (auto& object : m_movingObjects)
		{
			Player* player = dynamic_cast<Player*>(object.get());
			if (player)
			{
				SecondPlayer* secondPlayer = dynamic_cast<SecondPlayer*>(player);
				if (secondPlayer)
					return secondPlayer->getB2dPosition();
			}
		}
		return b2Vec2(100000, 100000);
	}


