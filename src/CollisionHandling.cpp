#include "CollisionHandling.h"
#include "GameObject.h"
#include "FirstPlayer.h"
#include "SecondPlayer.h"
#include "Wall.h"
#include "EnemyGhost.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Enemy.h"
#include "Heart.h"
#include "EnemySpider.h"
#include "EnemyBat.h"
#include "Coin.h"
#include "Gun.h"
#include "Sniper.h"
#include <memory>
#include "Bullet.h"
#include "GunBullet.h"
#include "sniperBullet.h"
#include "Throns.h"
#include "Fire.h"
#include "HealingBall.h"


CollisionHandling& CollisionHandling::instance()
{
    static CollisionHandling handler;
    return handler;
}

namespace // anonymous namespace — the standard way to make function "static"
{

    //First Player Colission with Second Player:
    //--------------------------------------------------------
    void firstPlayer2SecondPlayer(GameObject& firstPlayer, GameObject& secondPlayer) {}

    void secondPlayer2FirstPlayer(GameObject& secondPlayer, GameObject& firstPlayer)
    {
        firstPlayer2SecondPlayer(firstPlayer, secondPlayer);
    }


    //First Player Collision Collision With Wall:
    //--------------------------------------------------------
    void firstPlayer2Wall(GameObject& firstPlayer, GameObject& wall)
    {
        //Casting gameObject to FirstPlayer:
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        if (firstPlayerObject.getPosition().y < wall.getPosition().y)
        {
            firstPlayerObject.setCanJump(true);
            firstPlayerObject.setIsJumping(false);
        }
        else
        {
            firstPlayerObject.setCanJump(false);
            firstPlayerObject.setIsJumping(true);
        }
    }
    void wall2FirstPlayer(GameObject& wall, GameObject& firstPlayer)
    {
        firstPlayer2Wall(firstPlayer, wall);
    }

    //Second Player Collision With Wall:
    //--------------------------------------------------------
    void secondPlayer2Wall(GameObject& secondPlayer, GameObject& wall)
    {
        //casting:
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);

        if (secondPlayerObject.getPosition().y < wall.getPosition().y)
        {
            secondPlayerObject.setCanJump(true);
            secondPlayerObject.setIsJumping(false);
        }
        else
        {
            secondPlayerObject.setCanJump(false);
            secondPlayerObject.setIsJumping(true);
        }
    }

    void wall2SecondPlayer(GameObject& wall, GameObject& secondPlayer)
    {
        secondPlayer2Wall(secondPlayer, wall);
    }


    //First Player Collision With Ghost:
   //--------------------------------------------------------
    void firstPlayer2Ghost(GameObject& firstPlayer, GameObject& ghost)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.decreaseHealth(GHOST_DAMAGE);

		EnemyGhost& enemyGhostObject = dynamic_cast<EnemyGhost&>(ghost);
        enemyGhostObject.decreaseHealth(GHOST_HEALTH);
        Resources::instance().playSound(SoundTypes::decreaseHealth);
    }
    void ghost2FirstPlayer(GameObject& ghost, GameObject& firstPlayer)
    {firstPlayer2Ghost(firstPlayer, ghost);}

    //Second Player Collision With Ghost:
   //--------------------------------------------------------
    void secondPlayer2Ghost(GameObject& secondPlayer, GameObject& ghost)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.decreaseHealth(GHOST_DAMAGE);

        EnemyGhost& enemyGhostObject = dynamic_cast<EnemyGhost&>(ghost);
        enemyGhostObject.decreaseHealth(GHOST_HEALTH);
        Resources::instance().playSound(SoundTypes::decreaseHealth);
    }

    void ghost2SecondPlayer(GameObject& ghost, GameObject& secondPlayer)
    {secondPlayer2Ghost(secondPlayer, ghost);}

    //First Player Collision With Heart:
    //--------------------------------------------------------
    void firstPlayer2Heart(GameObject& firstPlayer, GameObject& heart)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.addHealth(HEART_HEALING);
        Resources::instance().playSound(SoundTypes::increaseHealth);

        Heart& heartObject = dynamic_cast<Heart&>(heart);
        heartObject.deleteObject();
    }

    void heart2FirstPlayer(GameObject& heart, GameObject& firstPlayer)
    {
        firstPlayer2Heart(firstPlayer, heart);
    }

    //Second Player Collision With Heart:
    //--------------------------------------------------------
    void secondPlayer2Heart(GameObject& secondPlayer,
        GameObject& heart)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.addHealth(HEART_HEALING);
        Resources::instance().playSound(SoundTypes::increaseHealth);

        Heart& heartObject = dynamic_cast<Heart&>(heart);
        heartObject.deleteObject();
    }

    void heart2SecondPlayer(GameObject& heart, GameObject& secondPlayer)
    {
        secondPlayer2Heart(secondPlayer, heart);
    }
    //--------------------------------------------------------



    //Spider  Collision With Wall:
    //--------------------------------------------------------
    void enemySpider2Wall(GameObject& enemy, GameObject& wall)
    {
        EnemySpider& spiderObject = dynamic_cast<EnemySpider&>(enemy);
        Wall& wallObject = dynamic_cast<Wall&>(wall);

        if (round(wallObject.getB2dPosition().y) == round(spiderObject.getB2dPosition().y))
        {
            if (spiderObject.getDirection() == Direction::Right)
                spiderObject.direction(sf::Keyboard::Left);

            else
                spiderObject.direction(sf::Keyboard::Right);

            spiderObject.bounce();
        }
    }

    void wall2EnemySpider(GameObject& wall, GameObject& enemy)
    {
        enemySpider2Wall(enemy, wall);
    }


    //Spider Collision With Heart:
    //--------------------------------------------------------
    void enemySpider2Heart(GameObject& enemy, GameObject& heart) {}

    void heart2EnemySpider(GameObject& heart, GameObject& enemy) { enemySpider2Heart(enemy, heart); }

    //Spider Collision With Heart:
    //--------------------------------------------------------
    void enemySpider2Coin(GameObject& enemy, GameObject& coin) {}

    void coin2EnemySpider(GameObject& coin, GameObject& enemy) { enemySpider2Coin(enemy, coin); }
    
    //Spider collesion to First Player:
    //--------------------------------------------------------
    void firstPlayer2EnemySpider(GameObject& player, GameObject& enemy)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(player);
        firstPlayerObject.decreaseHealth(SPIDER_DAMAGE);

        Resources::instance().playSound(SoundTypes::decreaseHealth);
    }
    
    void enemySpider2FirstPlayer(GameObject& enemy, GameObject& player)
    {firstPlayer2EnemySpider(player, enemy);}

    //Spider collesion to Second Player:
    //--------------------------------------------------------
    void enemySpider2SecondPlayer(GameObject& enemy, GameObject& player)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(player);
        secondPlayerObject.decreaseHealth(SPIDER_DAMAGE);

        Resources::instance().playSound(SoundTypes::decreaseHealth);
    }
    void secondPlayer2EnemySpider(GameObject& player, GameObject& enemy)
    {enemySpider2SecondPlayer(enemy, player);}

    //Spider collesion to Gun Bullet:
    //--------------------------------------------------------
    void enemySpider2GunBullet(GameObject& enemy, GameObject& bullet)
    {
        GunBullet& gunBulletObject = dynamic_cast<GunBullet&>(bullet);
        gunBulletObject.deleteObject();

        EnemySpider& SpiderObject = dynamic_cast<EnemySpider&>(enemy);
        SpiderObject.decreaseHealth(GUN_BULLET_DAMAGE);
        Resources::instance().playSound(SoundTypes::hitByBullet);
    }

    void gunBullet2EnemySpider(GameObject& bullet, GameObject& enemy)
    {enemySpider2GunBullet(enemy, bullet);}


    //Spider collesion to Sniper Bullet:
    //--------------------------------------------------------
    void EnemySpider2SniperBullet(GameObject& enemy, GameObject& sniperBullet)
    {
        SniperBullet& sniperBulletObject = dynamic_cast<SniperBullet&>(sniperBullet);
        sniperBulletObject.deleteObject();

        EnemySpider& SpiderObject = dynamic_cast<EnemySpider&>(enemy);
        SpiderObject.decreaseHealth(SNIPER_BULLET_DAMAGE);
        Resources::instance().playSound(SoundTypes::hitByBullet);
    }
    void sniperBullet2EnemySpider(GameObject& sniperBullet, GameObject& enemy)
    {EnemySpider2SniperBullet(enemy, sniperBullet);}

    //Bat Collision wiht Wall:
    void enemyBat2Wall(GameObject& enemy, GameObject& wall)
    {
        EnemyBat& batObject = dynamic_cast<EnemyBat&>(enemy);
        Wall& wallObject = dynamic_cast<Wall&>(wall);

        float batPosX = round(batObject.getB2dPosition().x);
        float batPosY = batObject.getB2dPosition().y;
        float wallPosX = wallObject.getB2dPosition().x;
        float wallPosY = wallObject.getB2dPosition().y;
        // Wall is to the right of the bat
        if (wallPosX > batPosX)
            batObject.bounce(Direction::Left);
        // Wall is to the left of the bat
        else
            batObject.bounce(Direction::Right);
    }

    void wall2EnemyBat(GameObject& wall, GameObject& enemy) { enemyBat2Wall(enemy, wall); }

    //Bat Collision with Heart:
    void enemyBat2Heart(GameObject& enemy, GameObject& heart) { }

    void heart2EnemyBat(GameObject& heart, GameObject& enemy) { enemyBat2Heart(enemy, heart); }

    void enemyBat2Coin(GameObject& enemy, GameObject& coin) { }

    void coin2EnemyBat(GameObject& coin, GameObject& enemy) { enemyBat2Coin(enemy, coin); }

    //First Player Collision With Coin:
    //--------------------------------------------------------
    void firstPlayer2Coin(GameObject& firstPlayer, GameObject& coin)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.setCoins(20);
        Resources::instance().playSound(SoundTypes::coinTaken);

        Coin& coinObject = dynamic_cast<Coin&>(coin);
        coinObject.deleteObject();
        Resources::instance().addTakenCoins();
    }
    void coin2FirstPlayer(GameObject& coin, GameObject& firstPlayer)
    {firstPlayer2Coin(firstPlayer, coin);}

    //Second Player Collision With Coin:
    //--------------------------------------------------------
    void secondPlayer2Coin(GameObject& secondPlayer,
        GameObject& coin)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.setCoins(20);
        Resources::instance().playSound(SoundTypes::coinTaken);

        Coin& coinObject = dynamic_cast<Coin&>(coin);
        coinObject.deleteObject();

        Resources::instance().addTakenCoins();
    }

    void coin2SecondPlayer(GameObject& coin, GameObject& secondPlayer)
    {secondPlayer2Coin(secondPlayer, coin);}



    //First Player Collesion With Thrones
    //------------------------------------------------------
    void firstPlayer2Throns(GameObject& firstPlayer, GameObject& throns)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.decreaseHealth(THORNS_DAMAGE);
        Resources::instance().playSound(SoundTypes::decreaseHealth);
     

        Throns& thronsObject = dynamic_cast<Throns&>(throns);
        thronsObject.deleteObject();
    }

    void throns2FirstPlayer(GameObject& throns,GameObject& firstPlayer)
    {firstPlayer2Throns(firstPlayer, throns);}


    //Second Player Collision With Thrones
   //------------------------------------------------------
    void secondPlayer2Throns(GameObject& secondPlayer,
        GameObject& throns)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.decreaseHealth(THORNS_DAMAGE);
        Resources::instance().playSound(SoundTypes::decreaseHealth);

        Throns& thronsObject = dynamic_cast<Throns&>(throns);
        thronsObject.deleteObject();

    }

    void throns2SecondPlayer(GameObject& throns,GameObject& secondPlayer)
    {secondPlayer2Throns(secondPlayer, throns);}
    
    
    //First Player Collesion With Gun
    //--------------------------------------------------------
    void firstPlayer2Gun(GameObject& firstPlayer,
        GameObject& gun)
    {
        Resources::instance().playSound(SoundTypes::handgunTaken);

        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        Gun& gunObject = dynamic_cast<Gun&>(gun);

        auto& textures = Resources::instance().getTextures();
        auto sprite = sf::Sprite();

        sprite.setTexture(textures[gunBullet]);
        GunBullet gunBulletObject(sprite, gunObject.getWeaponDir());

        firstPlayerObject.clearChosenWeapon();
        gunObject.deleteObject();
        firstPlayerObject.addWeapon(gunObject);

        gunBulletObject.setBulletDir(firstPlayerObject.getDirection());
        firstPlayerObject.addBullet(gunBulletObject);

        firstPlayerObject.getWeapon(firstPlayerObject.getWeaponCount() - 1).setChosen(true);
        firstPlayerObject.getWeapon(firstPlayerObject.getWeaponCount() - 1).setWeaponDir(firstPlayerObject.getDirection());
        firstPlayerObject.clearChosenBullet();
        firstPlayerObject.getBullet(firstPlayerObject.getWeaponCount() - 1).setChosen(true);
    }


    void gun2FirstPlayer(GameObject& gun,GameObject& firstPlayer)
    {firstPlayer2Gun(firstPlayer, gun);}

    //First Player Collesion With Sniper:
    //--------------------------------------------------------
    void firstPlayer2Sniper(GameObject& firstPlayer,
        GameObject& sniper)
    {
        Resources::instance().playSound(SoundTypes::handgunTaken);
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        Sniper& sniperObject = dynamic_cast<Sniper&>(sniper);

        auto& textures = Resources::instance().getTextures();
        auto sprite = sf::Sprite();

        sprite.setTexture(textures[sniperBullet]);
        SniperBullet sniperBulletObject(sprite, sniperObject.getWeaponDir());

        firstPlayerObject.clearChosenWeapon();

        sniperObject.deleteObject();
        firstPlayerObject.addWeapon(sniperObject);
        firstPlayerObject.addBullet(sniperBulletObject);

      
        firstPlayerObject.getWeapon(firstPlayerObject.getWeaponCount() - 1).setChosen(true);
        firstPlayerObject.clearChosenBullet();
        firstPlayerObject.getBullet(firstPlayerObject.getWeaponCount() - 1).setChosen(true);
    }

    void sniper2FirstPlayer(GameObject& sniper,GameObject& firstPlayer)
    {firstPlayer2Sniper(firstPlayer, sniper);}


    void secondPlayer2Gun(GameObject& secondPlayer,
        GameObject& gun)
    {
        Resources::instance().playSound(SoundTypes::handgunTaken);

        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        Gun& gunObject = dynamic_cast<Gun&>(gun);

        auto& textures = Resources::instance().getTextures();
        auto sprite = sf::Sprite();

        sprite.setTexture(textures[gunBullet]);
        GunBullet gunBulletObject(sprite, gunObject.getWeaponDir());

        secondPlayerObject.clearChosenWeapon();

        gunObject.deleteObject();
        secondPlayerObject.addWeapon(gunObject);
        secondPlayerObject.addBullet(gunBulletObject);

        secondPlayerObject.getWeapon(secondPlayerObject.getWeaponCount() - 1).setChosen(true);
        secondPlayerObject.clearChosenBullet();
        secondPlayerObject.getBullet(secondPlayerObject.getWeaponCount() - 1).setChosen(true);
    }

    void gun2SecondPlayer(GameObject& gun,GameObject& secondPlayer)
    {secondPlayer2Gun(secondPlayer, gun);}

    void secondPlayer2Sniper(GameObject& secondPlayer,
        GameObject& sniper)
    {

        Resources::instance().playSound(SoundTypes::handgunTaken);
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        Sniper& sniperObject = dynamic_cast<Sniper&>(sniper);

        auto& textures = Resources::instance().getTextures();
        auto sprite = sf::Sprite();

        sprite.setTexture(textures[sniperBullet]);
        SniperBullet sniperBulletObject(sprite, sniperObject.getWeaponDir());

        secondPlayerObject.clearChosenWeapon();

        sniperObject.deleteObject();
        secondPlayerObject.addWeapon(sniperObject);
        secondPlayerObject.addBullet(sniperBulletObject);

        secondPlayerObject.getWeapon(secondPlayerObject.getWeaponCount() - 1).setChosen(true);
        secondPlayerObject.clearChosenBullet();
        secondPlayerObject.getBullet(secondPlayerObject.getWeaponCount() - 1).setChosen(true);
    }

    void sniper2SecondPlayer(GameObject& sniper,GameObject& secondPlayer)
    {secondPlayer2Sniper(secondPlayer, sniper);}
    //--------------------------------------------------------

    //First Player Collesion With bat
    //--------------------------------------------------------
    void firstPlayer2EnemyBat(GameObject& firstPlayer,GameObject& enemyBat)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.decreaseHealth(BAT_DAMAGE);

        EnemyBat& enemyBatObject = dynamic_cast<EnemyBat&>(enemyBat);
        enemyBatObject.decreaseHealth(BAT_HEALTH);
        Resources::instance().playSound(SoundTypes::decreaseHealth);
    }

    void enemyBat2FirstPlayer(GameObject& enemyBat,GameObject& firstPlayer)
    {firstPlayer2EnemyBat(firstPlayer, enemyBat);}


    //Second Player Collesion With bat
   //--------------------------------------------------------
    void secondPlayer2EnemyBat(GameObject& secondPlayer,
        GameObject& enemyBat)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.decreaseHealth(BAT_DAMAGE);

        EnemyBat& enemyBatObject = dynamic_cast<EnemyBat&>(enemyBat);
        enemyBatObject.decreaseHealth(BAT_HEALTH);
        Resources::instance().playSound(SoundTypes::decreaseHealth);
    }

    void enemyBat2SecondPlayer(GameObject& enemyBat,GameObject& secondPlayer)
    {secondPlayer2EnemyBat(secondPlayer, enemyBat);}
    

    //Gun Bullet Collision to Wall:
    //----------------------------------------------------------------------
    void gunBullet2Wall(GameObject& gunBullet,
        GameObject& wall)
    {
        GunBullet& gunBulletObject = dynamic_cast<GunBullet&>(gunBullet);
        gunBulletObject.deleteObject();
    }

    void wall2GunBullet(GameObject& wall,GameObject& gunBullet)
    {gunBullet2Wall(gunBullet, wall);}


    // Gun Bullet Collesion With Enemy Bat:
    //----------------------------------------------------------------------
    void gunBullet2EnemyBat(GameObject& gunBullet,
        GameObject& enemyBat)
    {
        GunBullet& gunBulletObject = dynamic_cast<GunBullet&>(gunBullet);
        gunBulletObject.deleteObject();

        EnemyBat& enemyBatObject = dynamic_cast<EnemyBat&>(enemyBat);
        enemyBatObject.decreaseHealth(GUN_BULLET_DAMAGE);
        Resources::instance().playSound(SoundTypes::hitByBullet);
    }
    
    void enemyBat2GunBullet(GameObject& enemyBat,GameObject& gunBullet)
    {gunBullet2EnemyBat(gunBullet, enemyBat);}


     // Gun Bullet Collesion With First Player:
     //----------------------------------------------------------------------
    void gunBullet2FirstPlayer(GameObject& gunBullet,
        GameObject& firstPlayer)
    {
        GunBullet& gunBulletObject = dynamic_cast<GunBullet&>(gunBullet);
        gunBulletObject.deleteObject();
        if (Resources::instance().getFriendlyFire())
        {
            FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
            firstPlayerObject.decreaseHealth(GUN_BULLET_DAMAGE);
            Resources::instance().playSound(SoundTypes::hitByBullet);
        }
    }
    void firstPlayer2GunBullet(GameObject& firstPlayer,GameObject& gunBullet)
    {gunBullet2FirstPlayer(gunBullet, firstPlayer);}


    // Gun Bullet Collesion With Second Player:
    //----------------------------------------------------------------------
    void gunBullet2SecondPlayer(GameObject& gunBullet,GameObject& secondPlayer)
    {
        GunBullet& gunBulletObject = dynamic_cast<GunBullet&>(gunBullet);
        gunBulletObject.deleteObject();
        if (Resources::instance().getFriendlyFire())
        {
            SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
            secondPlayerObject.decreaseHealth(GUN_BULLET_DAMAGE);
            Resources::instance().playSound(SoundTypes::hitByBullet);
        }
    }
    void secondPlayer2GunBullet(GameObject& secondPlayer,GameObject& gunBullet)
    {gunBullet2SecondPlayer(gunBullet, secondPlayer);}

    // Gun Bullet Collesion With 
    //----------------------------------------------------------------------
    void gunBullet2EnemyGhost(GameObject& gunBullet, GameObject& ghost)
    {
        GunBullet& gunBulletObject = dynamic_cast<GunBullet&>(gunBullet);
        gunBulletObject.deleteObject();

        EnemyGhost& enemyGhost = dynamic_cast<EnemyGhost&>(ghost);
        enemyGhost.decreaseHealth(GUN_BULLET_DAMAGE);
        Resources::instance().playSound(SoundTypes::hitByBullet);
      
    }
    void enemyGhostGunBullet(GameObject& ghost, GameObject& gunBullet)
    {gunBullet2EnemyGhost(gunBullet, ghost);}

    // Sniper Bullet Collesion With Wall:
     //----------------------------------------------------------------------
    void sniperBullet2Wall(GameObject& sniperBullet,
        GameObject& wall)
    {
        SniperBullet& sniperBulletObject = dynamic_cast<SniperBullet&>(sniperBullet);
        sniperBulletObject.deleteObject();
    }

    void wall2SniperBullet(GameObject& wall,GameObject& sniperBullet)
    {sniperBullet2Wall(sniperBullet, wall);}


    // Sniper Bullet Collesion With Bat:
    //----------------------------------------------------------------------
    void sniperBullet2EnemyBat(GameObject& sniperBullet,GameObject& enemyBat)
    {
        SniperBullet& sniperBulletObject = dynamic_cast<SniperBullet&>(sniperBullet);
        sniperBulletObject.deleteObject();

        EnemyBat& enemyBatObject = dynamic_cast<EnemyBat&>(enemyBat);
        enemyBatObject.decreaseHealth(SNIPER_BULLET_DAMAGE);
    }

    void enemyBat2SniperBullet(GameObject& enemyBat,GameObject& sniperBullet)
    {sniperBullet2EnemyBat(sniperBullet, enemyBat);}

    // Sniper Bullet Collesion With GHOST:
    //----------------------------------------------------------------------
    void sniperBullet2EnemyGhost(GameObject& sniperBullet, GameObject& ghost)
    {
        SniperBullet& sniperBulletObject = dynamic_cast<SniperBullet&>(sniperBullet);
        sniperBulletObject.deleteObject();

        EnemyGhost& ghostObject = dynamic_cast<EnemyGhost&>(ghost);
        ghostObject.decreaseHealth(SNIPER_BULLET_DAMAGE);
    }
    void enemyGhost2SniperBullet(GameObject& ghost, GameObject& sniperBullet)
    {sniperBullet2EnemyGhost(sniperBullet, ghost);}


    // Sniper Bullet Collesion With First Player:
    //----------------------------------------------------------------------
    void sniperBullet2FirstPlayer(GameObject& sniperBullet,
        GameObject& firstPlayer)
    {
        SniperBullet& sniperBulletObject = dynamic_cast<SniperBullet&>(sniperBullet);
        sniperBulletObject.deleteObject();
        if (Resources::instance().getFriendlyFire())
        {
            FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
            firstPlayerObject.decreaseHealth(SNIPER_BULLET_DAMAGE);
            Resources::instance().playSound(SoundTypes::hitByBullet);
        }
    }

    void firstPlayer2SniperBullet(GameObject& firstPlayer,GameObject& sniperBullet)
    {sniperBullet2FirstPlayer(sniperBullet, firstPlayer);}


    // Sniper Bullet Collesion With Second Player:
    //----------------------------------------------------------------------
    void sniperBullet2SecondPlayer(GameObject& sniperBullet,
        GameObject& secondPlayer)
    {
        SniperBullet& sniperBulletObject = dynamic_cast<SniperBullet&>(sniperBullet);
        sniperBulletObject.deleteObject();
        if (Resources::instance().getFriendlyFire())
        {
            SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
            secondPlayerObject.decreaseHealth(SNIPER_BULLET_DAMAGE);
            Resources::instance().playSound(SoundTypes::hitByBullet);
        }
    }
    void secondPlayer2SniperBullet(GameObject& secondPlayer,GameObject& sniperBullet)
    {sniperBullet2SecondPlayer(sniperBullet, secondPlayer);}
    

    // Fire Collesion With First Player:
    //----------------------------------------------------------------------
    void firstPlayer2Fire(GameObject& firstPlayer, GameObject& fire)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.decreaseHealth(0.1f);
        Resources::instance().playSound(SoundTypes::fireSound);
    }
    void fire2FirstPlayer(GameObject& fire,GameObject& firstPlayer)
    {firstPlayer2Fire(firstPlayer, fire);}

    // Fire Collesion With Second Player:
   //----------------------------------------------------------------------
    void secondPlayer2Fire(GameObject& secondPlayer,GameObject& fire)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.decreaseHealth(0.1f);
        Resources::instance().playSound(SoundTypes::fireSound);
    }

    void fire2SecondPlayer(GameObject& fire,GameObject& secondPlayer)
    {secondPlayer2Fire(secondPlayer, fire);}


    // Healing Ball Collesion With First Player:
   //----------------------------------------------------------------------
    void firstPlayer2HealingBall(GameObject& firstPlayer, GameObject& healingBall)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.addHealth(0.1f);
        Resources::instance().playSound(SoundTypes::healSound);
    }

    void healingBall2FirstPlayer(GameObject& healingBall,GameObject& firstPlayer)
    {firstPlayer2HealingBall(firstPlayer, healingBall);}

    // Healing Ball Collesion With Second Player:
   //----------------------------------------------------------------------
    void secondPlayer2HealingBall(GameObject& secondPlayer,GameObject& healingBall)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.addHealth(0.1f);
        Resources::instance().playSound(SoundTypes::healSound);
    }

    void healingBall2SecondPlayer(GameObject& HealingBall,GameObject& secondPlayer)
    {secondPlayer2HealingBall(secondPlayer, HealingBall);}
}

CollisionsTable CollisionHandling::initializeTable()
{
    CollisionsTable table;

    //first to second
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(SecondPlayer))] = &firstPlayer2SecondPlayer;
    table[Key(typeid(SecondPlayer), typeid(FirstPlayer))] = &secondPlayer2FirstPlayer;
    //-----------------------------------------------------------------------

    //first and second to wall
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(Wall))] = &firstPlayer2Wall;
    table[Key(typeid(Wall), typeid(FirstPlayer))] = &wall2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(Wall))] = &secondPlayer2Wall;
    table[Key(typeid(Wall), typeid(SecondPlayer))] = &wall2SecondPlayer;
    //-----------------------------------------------------------------------
    
    //first and second to heart
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(EnemyGhost))] = &firstPlayer2Ghost;
    table[Key(typeid(EnemyGhost), typeid(FirstPlayer))] = &ghost2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(EnemyGhost))] = &secondPlayer2Ghost;
    table[Key(typeid(EnemyGhost), typeid(SecondPlayer))] = &ghost2SecondPlayer;

    //first and second to heart
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(Heart))] = &firstPlayer2Heart;
    table[Key(typeid(Heart), typeid(FirstPlayer))] = &heart2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(Heart))] = &secondPlayer2Heart;
    table[Key(typeid(Heart), typeid(SecondPlayer))] = &heart2SecondPlayer;
    //-----------------------------------------------------------------------

    //first and second to coin
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(Coin))] = &firstPlayer2Coin;
    table[Key(typeid(Coin), typeid(FirstPlayer))] = &coin2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(Coin))] = &secondPlayer2Coin;
    table[Key(typeid(Coin), typeid(SecondPlayer))] = &coin2SecondPlayer;
    //-----------------------------------------------------------------------

    //enemy spider to statics
    //-----------------------------------------------------------------------
    table[Key(typeid(EnemySpider), typeid(Wall))] = &enemySpider2Wall;
    table[Key(typeid(Wall), typeid(EnemySpider))] = &wall2EnemySpider;

    table[Key(typeid(EnemySpider), typeid(Heart))] = &enemySpider2Heart;
    table[Key(typeid(Heart), typeid(EnemySpider))] = &heart2EnemySpider;

    table[Key(typeid(EnemySpider), typeid(Coin))] = &enemySpider2Coin;
    table[Key(typeid(Coin), typeid(EnemySpider))] = &coin2EnemySpider;


    table[Key(typeid(EnemySpider), typeid(FirstPlayer))] = &enemySpider2FirstPlayer;
    table[Key(typeid(FirstPlayer), typeid(EnemySpider))] = &firstPlayer2EnemySpider;


    table[Key(typeid(EnemySpider), typeid(SecondPlayer))] = &enemySpider2SecondPlayer;
    table[Key(typeid(SecondPlayer), typeid(EnemySpider))] = &secondPlayer2EnemySpider;

    
    table[Key(typeid(EnemySpider), typeid(GunBullet))] = &enemySpider2GunBullet;
    table[Key(typeid(GunBullet), typeid(EnemySpider))] = &gunBullet2EnemySpider;
    
    table[Key(typeid(EnemySpider), typeid(SniperBullet))] = &EnemySpider2SniperBullet;
    table[Key(typeid(SniperBullet), typeid(EnemySpider))] = &sniperBullet2EnemySpider;

    //-----------------------------------------------------------------------
    //enemy bat to statics
    //-----------------------------------------------------------------------
    table[Key(typeid(EnemyBat), typeid(Wall))] = &enemyBat2Wall;
    table[Key(typeid(Wall), typeid(EnemyBat))] = &wall2EnemyBat;

    table[Key(typeid(EnemyBat), typeid(Heart))] = &enemyBat2Heart;
    table[Key(typeid(Heart), typeid(EnemyBat))] = &heart2EnemyBat;

    table[Key(typeid(EnemyBat), typeid(Coin))] = &enemyBat2Coin;
    table[Key(typeid(Coin), typeid(EnemyBat))] = &coin2EnemyBat;
    //players to weapons
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(Gun))] = &firstPlayer2Gun;
    table[Key(typeid(Gun), typeid(FirstPlayer))] = &gun2FirstPlayer;

    table[Key(typeid(FirstPlayer), typeid(Sniper))] = &firstPlayer2Sniper;
    table[Key(typeid(Sniper), typeid(FirstPlayer))] = &sniper2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(Gun))] = &secondPlayer2Gun;
    table[Key(typeid(Gun), typeid(SecondPlayer))] = &gun2SecondPlayer;

    table[Key(typeid(SecondPlayer), typeid(Sniper))] = &secondPlayer2Sniper;
    table[Key(typeid(Sniper), typeid(SecondPlayer))] = &sniper2SecondPlayer;
    //-----------------------------------------------------------------------
    //first and second to enemy bat
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(EnemyBat))] = &firstPlayer2EnemyBat;
    table[Key(typeid(EnemyBat), typeid(FirstPlayer))] = &enemyBat2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(EnemyBat))] = &secondPlayer2EnemyBat;
    table[Key(typeid(EnemyBat), typeid(SecondPlayer))] = &enemyBat2SecondPlayer;
    //-----------------------------------------------------------------------
     //first and second to throns
    //-----------------------------------------------------------------------
    table[Key(typeid(FirstPlayer), typeid(Throns))] = &firstPlayer2Throns;
    table[Key(typeid(Throns), typeid(FirstPlayer))] = &throns2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(Throns))] = &secondPlayer2Throns;
    table[Key(typeid(Throns), typeid(SecondPlayer))] = &throns2SecondPlayer;
    //------------------------------------------------------------------------
    //gunBullet to wall
    //------------------------------------------------------------------------
    table[Key(typeid(GunBullet), typeid(Wall))] = &gunBullet2Wall;
    table[Key(typeid(Wall), typeid(GunBullet))] = &wall2GunBullet;
    //-------------------------------------------------------------------------
    //gunBullet to enemyBat
    table[Key(typeid(GunBullet), typeid(EnemyBat))] = &gunBullet2EnemyBat;
    table[Key(typeid(EnemyBat), typeid(GunBullet))] = &enemyBat2GunBullet;
    //-----------------------------------------------------------------------
    //gunBullet to firstPlayer
    //-----------------------------------------------------------------------
    table[Key(typeid(GunBullet), typeid(FirstPlayer))] = &gunBullet2FirstPlayer;
    table[Key(typeid(FirstPlayer), typeid(GunBullet))] = &firstPlayer2GunBullet;
    //-------------------------------------------------------------------------
    //GunBullet to second player
    table[Key(typeid(GunBullet), typeid(SecondPlayer))] = &gunBullet2SecondPlayer;
    table[Key(typeid(SecondPlayer), typeid(GunBullet))] = &secondPlayer2GunBullet;

    //GunBullet to Ghost
    //-------------------------------------------------------------------------
    table[Key(typeid(GunBullet), typeid(EnemyGhost))] = &gunBullet2EnemyGhost;
    table[Key(typeid(EnemyGhost), typeid(GunBullet))] = &enemyGhostGunBullet;
    //---------------------------------------------------------------------------
    //sniper bullet to first player
    table[Key(typeid(SniperBullet), typeid(FirstPlayer))] = &sniperBullet2FirstPlayer;
    table[Key(typeid(FirstPlayer), typeid(SniperBullet))] = &firstPlayer2SniperBullet;
    //-------------------------------------------------------------------------
    //sniper Bullet to second player
    table[Key(typeid(SniperBullet), typeid(SecondPlayer))] = &sniperBullet2SecondPlayer;
    table[Key(typeid(SecondPlayer), typeid(SniperBullet))] = &secondPlayer2SniperBullet;
    //-----------------------------------------------------------------------------
    //sniper bullet wall
    table[Key(typeid(SniperBullet), typeid(Wall))] = &sniperBullet2Wall;
    table[Key(typeid(Wall), typeid(SniperBullet))] = &wall2SniperBullet;
    //------------------------------------------------------------------------------
    //sniper bullet to enemybat
    table[Key(typeid(SniperBullet), typeid(EnemyBat))] = &sniperBullet2EnemyBat;
    table[Key(typeid(EnemyBat), typeid(SniperBullet))] = &enemyBat2SniperBullet;

    //sniper bullet to ghost:
    //------------------------------------------------------------------------------
    table[Key(typeid(SniperBullet), typeid(EnemyGhost))] = &sniperBullet2EnemyGhost;
    table[Key(typeid(EnemyGhost), typeid(SniperBullet))] = &enemyGhost2SniperBullet;
    //-----------------------------------------------------------------------------
    //fire to players
    table[Key(typeid(FirstPlayer), typeid(Fire))] = &firstPlayer2Fire;
    table[Key(typeid(Fire), typeid(FirstPlayer))] = &fire2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(Fire))] = &secondPlayer2Fire;
    table[Key(typeid(Fire), typeid(SecondPlayer))] = &fire2SecondPlayer;
    //---------------------------------------------------------------------------
    //healing ball to players
    table[Key(typeid(FirstPlayer), typeid(HealingBall))] = &firstPlayer2HealingBall;
    table[Key(typeid(HealingBall), typeid(FirstPlayer))] = &healingBall2FirstPlayer;

    table[Key(typeid(SecondPlayer), typeid(HealingBall))] = &secondPlayer2HealingBall;
    table[Key(typeid(HealingBall), typeid(SecondPlayer))] = &healingBall2SecondPlayer;
    return table;
}

CollisionFunc CollisionHandling::search(const std::type_index& object_a, const std::type_index& object_b)
{
    static auto	table = initializeTable();

    auto table_entry = table.find(std::make_pair(object_a, object_b));

    if (table_entry == table.end())
    {
        return nullptr;
    }

    return table_entry->second;
}

void CollisionHandling::handleCollision(GameObject& object_a, GameObject& object_b)
{
    auto collision_func = search(typeid(object_a), typeid(object_b));

    if (collision_func)
        collision_func(object_a, object_b);
}
