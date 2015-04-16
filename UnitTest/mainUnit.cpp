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
    Ally a;
    l.setLevelNumber(4);
    a.setScore(l.getLevelNumber()*2);

    BOOST_CHECK(a.getScore() == 28);
}

/*******************************
    Unit Test for the Bullet
********************************/

/*******************************
    Unit Test for the Enemy
********************************/

BOOST_AUTO_TEST_CASE(colisionEnemyAndBullet){
    Enemy* e = new Enemy(50,40,40);
    Bullet* b = new Bullet(50,50, 20);

    BOOST_CHECK(e->collisions(b) == true);
}

BOOST_AUTO_TEST_CASE(notcColisionAllyAndEnemy){
    Enemy* e = new Enemy(50,40,40);
    Ally* a = new Ally(146,50,20);

    BOOST_CHECK(a->collisions(e) == false);
}
/*******************************
    Unit Test for the Level
********************************/

/***************
BOOST_AUTO_TEST_CASE(colisionAllyAndAllBullets){
    Ally* a = new Ally();
    int defaultLife=a->getHealth();
std::cout << "vie initial " << a->getHealth() << std::endl;
    Level* l = new Level();
    Enemy* e = new Enemy();
std::cout << "WEEEEEEEEEEEEEEEESH" << std::endl;
    e->shoot();
    e->shoot();
    e->move(a->getX(), a->getY());
    e->shoot();
    e->move(148, 234);

    l->checkCollisions();
std::cout << "vie finale " << a->getHealth() << std::endl;

    BOOST_CHECK(defaultLife != a->getHealth());
}*/

//check if the level is finish when all enemies and the boss are dead
BOOST_AUTO_TEST_CASE(endingLevel){
    Level* l = new Level();

    l->deleteAllEnemy();

    BOOST_CHECK(l->isFinish() == true );
}

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

BOOST_AUTO_TEST_CASE(bossNotExist){
    Level* l = new Level();

    BOOST_CHECK(l->getBoss() ==nullptr );
}

BOOST_AUTO_TEST_CASE(bossExist){
    Level* l = new Level();
    l->addBoss();

    BOOST_CHECK(l->getBoss() != nullptr );
}

BOOST_AUTO_TEST_CASE(newsEnemies){
    Level* l = new Level();

    l->addEnemies();

    BOOST_CHECK(l->getNumberOfEnemies() >0 );
}
/**************
BOOST_AUTO_TEST_CASE(moveEnemies){
    Level* l = new Level();

    bool move = true;

    std::vector<Enemy*> enemies = l->getEnemies();

    l->moveEnemies();

    std::vector<Enemy*> enemiesMoving = l->getEnemies();

    for(int i = 0; i<enemies.size() && i<enemiesMoving.size(); i++){
        std::cout << enemies[i]->getX() << std::endl;
        std::cout << enemiesMoving[i]->getX() << std::endl << std::endl;
        if(enemies[i]->getX() == enemiesMoving[i]->getX()
            //&& enemies[i]->getY() == enemiesMoving[i]->getY() //car dansmoveEnemies on chositi de ne changement que x
           ){
            move=false;
            break;
        }
    }

    BOOST_CHECK(move == true);
}
*/
BOOST_AUTO_TEST_CASE(enemiesShoot){
    Level* l = new Level();

    l->EnemiesShoot();

    BOOST_CHECK(l->getNumberOfBullets() > 0);
}

/*******************************
    Unit Test for the Ship
********************************/
//change Ally position
BOOST_AUTO_TEST_CASE(moveAlly){
    Ally a;
    a.move(45, 67);

    BOOST_CHECK(a.getX()==45 && a.getY()==67);
}

//change Enemy position
BOOST_AUTO_TEST_CASE(moveEnemy){
    Enemy e;
    e.move(45, 67);

    BOOST_CHECK(e.getX()==45 && e.getY()==67);
}

//change boss position
BOOST_AUTO_TEST_CASE(moveBoss){
    Boss b;
    b.move(45, 67);

    BOOST_CHECK(b.getX()==45 && b.getY()==67);
}

//check if we can't move a GraphicElement (hear the ally) except the game area
BOOST_AUTO_TEST_CASE(moveAllyExceptArea){
    Ally a;
    a.move(50, 0);
    a.move(-45, -67);

    BOOST_CHECK(a.getX()==50 && a.getY()==0);
}

BOOST_AUTO_TEST_CASE(setDamageToAlly){
    Ally a;
    a.setDamage(50);

    BOOST_CHECK(a.getDamage()==50);
}

/***************
BOOST_AUTO_TEST_CASE(shootBullet){
    Ally* a = new Ally();
    Enemy *e = new Enemy();
    Level* l = new Level();

    int nbBalle = l->getNumberOfBullets();

    a->shoot();
    nbBalle++;
    e->shoot();
    nbBalle++;

    BOOST_CHECK(nbBalle == l->getNumberOfBullets());
}
*/

/*******************************
    Unit Test for the Menu
********************************/
//
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
