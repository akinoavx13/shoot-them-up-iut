//
//  mainUnit.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 25/02/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE

#include <boost/test/unit_test.hpp>
#include <vector>

#include "../ShootThemUp/Ally.h"
#include "../ShootThemUp/Level.h"
#include "../ShootThemUp/Enemy.h"
#include "../ShootThemUp/Boss.h"
#include "../ShootThemUp/Player.h"
#include "../ShootThemUp/Menu.h"
#include "../ShootThemUp/Bullet.h"


/*******************************
    Unit Test for the Ally
********************************/

//check if at the beginning the player is alive
BOOST_AUTO_TEST_CASE(alive){
    Ally a;

    BOOST_CHECK(a.isDead() == false && a.isOver()==false);
}

//check if the player haven't life
BOOST_AUTO_TEST_CASE(dead){
    Ally a;
    a.setNumberOfLife(0);

    BOOST_CHECK(a.isOver() == true);
}

//check if the player haven't health points
BOOST_AUTO_TEST_CASE(loseLife){
    Ally a;
    a.setHealth(0);

    BOOST_CHECK(a.isDead() == true);
}

//check if at the beginning the player have 3 lifes
BOOST_AUTO_TEST_CASE(defaultLife){
    Ally a;

    BOOST_CHECK(a.getNumberOfLife() == 3);
}

//check if we can increment life correctly
BOOST_AUTO_TEST_CASE(incrementLife){
    Ally a;
    int life = a.getNumberOfLife();
    a.setNumberOfLife(life+1);

    BOOST_CHECK(a.getNumberOfLife() == 4);
}

//check if at the level 4, the player have 20+4*2 points
BOOST_AUTO_TEST_CASE(scored){
    Level l;
    l.setLevelNumber(4);
    l.getAlly()->setScore(l.getLevelNumber()*2);

    BOOST_CHECK(l.getAlly()->getScore() == 28);
}

/*******************************
    Unit Test for the Bullet
********************************/

/*******************************
    Unit Test for the Enemy
********************************/

//check there is collision between an enemy and bullet if there are the same position
BOOST_AUTO_TEST_CASE(collisionEnemyAndBullet){
    Enemy* e = new Enemy(50,40,40);
    Bullet* b = new Bullet(50,50, 20);

    BOOST_CHECK(e->collisions(b) == true);
}

//check there isn't collision between ally and an enemy if there aren't the same position
BOOST_AUTO_TEST_CASE(notcColisionAllyAndEnemy){
    Enemy* e = new Enemy(50,40,40);
    Ally* a = new Ally(146,50,20);

    BOOST_CHECK(a->collisions(e) == false);
}

/*******************************
    Unit Test for the Level
********************************/

//check if the ally is attack by enemies
BOOST_AUTO_TEST_CASE(colisionAllyAndAllBullets){
    Level* l = new Level();

    l->getAlly()->move(50, 0);

    //there are 3 enemies at the beginning
    l->getEnemies()[0]->move(50, 100);
    l->getEnemies()[1]->move(100, 100);
    l->getEnemies()[2]->move(150, 100);

    l->EnemiesShoot();

    l->checkCollisions();

    //because enemies can be tiny, submarine or mighty
    BOOST_CHECK(l->getAlly()->getHealth() == 80 || l->getAlly()->getHealth() == 60 || l->getAlly()->getHealth() == 50);
}

//check if the level is finish when all enemies and the boss are dead
BOOST_AUTO_TEST_CASE(endingLevel){
    Level* l = new Level();

    //if we kill all enemies, we delete all
    l->deleteAllEnemy();
    //we add a boss
    l->addBoss();

    //we create a bullet with boss position and health : it's more easy to test because he will kill in one case
    Bullet* b1 = new Bullet(l->getBoss()->getX(), l->getBoss()->getY(), l->getBoss()->getHealth());
    l->addBullet(b1);
    l->checkCollisions();

    BOOST_CHECK(l->isFinish() == true );
}

//check if bullets will add
BOOST_AUTO_TEST_CASE(newsBullets){
    Bullet* b1 = new Bullet();
    Bullet* b2 = new Bullet();
    Bullet* b3 = new Bullet();

    Level* l = new Level();

    l->addBullet(b1);
    l->addBullet(b2);
    l->addBullet(b3);

    BOOST_CHECK(l->getNumberOfBullets() == 3 );
}

//check if at the beginning the boss don't exist
BOOST_AUTO_TEST_CASE(bossNotExist){
    Level* l = new Level();

    BOOST_CHECK(l->getBoss() ==nullptr );
}

//check if we add boss, he exist
BOOST_AUTO_TEST_CASE(bossExist){
    Level* l = new Level();
    l->addBoss();

    BOOST_CHECK(l->getBoss() != nullptr );
}

//check if the numbers of enemies is the same that the constancy at the beginning
BOOST_AUTO_TEST_CASE(newsEnemies){
    Level* l = new Level();

    l->addEnemies();

    BOOST_CHECK(l->getNumberOfEnemies() > DEFAULT_LEVEL_ENEMY_NUMBER);
}

//check if the enemies position change
BOOST_AUTO_TEST_CASE(moveEnemies){
    Level* l = new Level();

    l->getEnemies()[0]->move(50, 50);
    l->getEnemies()[1]->move(100, 100);
    l->getEnemies()[2]->move(150, 150);

    l->moveEnemies();

    BOOST_CHECK(l->getEnemies()[0]->getX() != 50  && l->getEnemies()[0]->getX() != 50 &&
                l->getEnemies()[1]->getX() != 100 && l->getEnemies()[1]->getX() != 100 &&
                l->getEnemies()[2]->getX() != 150 && l->getEnemies()[2]->getX() != 150);
}

//all enemies shoot, so check if the number of bullets is the same that the number of enemies
BOOST_AUTO_TEST_CASE(enemiesShoot){
    Level* l = new Level();

    l->EnemiesShoot();

    BOOST_CHECK(l->getNumberOfBullets() == DEFAULT_LEVEL_ENEMY_NUMBER);
}

/*******************************
    Unit Test for the Ship
********************************/
//change Ally position
BOOST_AUTO_TEST_CASE(moveAlly){
    Ally a;
    a.move(45, 67);

    BOOST_CHECK(a.getX() == 45 && a.getY() == 67);
}

//change Enemy position
BOOST_AUTO_TEST_CASE(moveEnemy){
    Enemy e;
    e.move(45, 67);

    BOOST_CHECK(e.getX() == 45 && e.getY() == 67);
}

//change boss position
BOOST_AUTO_TEST_CASE(moveBoss){
    Boss b;
    b.move(45, 67);

    BOOST_CHECK(b.getX() == 45 && b.getY() == 67);
}

//check if we can't move a GraphicElement (hear the ally) except the game area
BOOST_AUTO_TEST_CASE(moveAllyExceptArea){
    Ally a;
    a.move(50, 0);
    a.move(-45, -67);

    BOOST_CHECK(a.getX() == 50 && a.getY() == 0);
}

//setter of ship damage
BOOST_AUTO_TEST_CASE(setDamageToAlly){
    Ally a;
    a.setDamage(50);

    BOOST_CHECK(a.getDamage() == 50);
}

//the same test that before, with the ally
BOOST_AUTO_TEST_CASE(shootBullet){
    Level* l = new Level();

    l->EnemiesShoot();
    l->getAlly()->shoot();

    BOOST_CHECK(l->getNumberOfBullets() == DEFAULT_LEVEL_ENEMY_NUMBER + 1);
}

/*******************************
    Unit Test for the Menu
********************************/
//check if the file y correct : it must have string and int value
BOOST_AUTO_TEST_CASE(showScoresCorrectly){
    Menu* m;
    std::vector<Player> p = m->showScores(LINUX_SCORE_FILE);

    bool good = true;

    for(int i = 0; i<p.size(); i++){
        if(p[i].getName()=="" || !p[i].getScore()){
            good = false;
            break;
        }
    }

    BOOST_CHECK(good == true);
}

/*******************************
    Unit Test for the Player
********************************/
//check if Nicolas exist : we know that yes
BOOST_AUTO_TEST_CASE(playerExist){
    Menu m;
    std::vector<Player> it = m.showScores(LINUX_SCORE_FILE);
    Player p("Nicolas", 100);
    bool find = false;
    for(auto test : it){
        if(test.alreadyExist(p)){
            find = true;
            break;
        }
    }

    BOOST_CHECK(find == true);
}

//check if Jacqui exist : we know that no
BOOST_AUTO_TEST_CASE(playerNotExist){
    Menu m;
    std::vector<Player> it = m.showScores(LINUX_SCORE_FILE);
    Player p("Jacqui", 100);
    bool find = false;
    for(auto test : it){
        if(test.alreadyExist(p)){
            find = true;
            break;
        }
    }
    BOOST_CHECK(find == false);
}

//In the file, Nicolas best score if around 50, so now, it maybe 10000
BOOST_AUTO_TEST_CASE(bestScore){
    Menu m;
    std::vector<Player> it = m.showScores(LINUX_SCORE_FILE);
    Player p("Nicolas", 10000);
    int value = 0;
    for(auto test : it){
        if(test.alreadyExist(p)){
            test.bestScore(p.getScore());
            value=test.getScore();
        }
    }
    BOOST_CHECK(value == 10000);
}

//In the file, Nicolas best score if around 50, so now, it maybe superior than 4
BOOST_AUTO_TEST_CASE(notBestScore){
    Menu m;
    std::vector<Player> it = m.showScores(LINUX_SCORE_FILE);
    Player p("Nicolas", 4);
    int value = 0;
    for(auto test : it){
        if(test.alreadyExist(p)){
            test.bestScore(p.getScore());
            value=test.getScore();
        }
    }
    BOOST_CHECK(value > 4);
}
