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

/*******************************
    Unit Test for the Level
********************************/

//check if the level is finish when all enemies and the boss are dead
BOOST_AUTO_TEST_CASE(endingLevel){
    Level l;
    std::vector<Enemy*> enemies = l.getEnemies();
    Boss* b = new Boss();

    for(auto e : enemies){
        e->setHealth(0);
    }

    l.addBoss();
    b=l.getBoss();
    b->setHealth(0);

    std::cout << enemies.size() << std::endl;

    std::cout << b->toString() << std::endl;

    //on voit qu'il y a un problème avec ka suppression

    //BOOST_CHECK(l.isFinish() == true );
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
/*******************************
    Unit Test for the Menu
********************************/

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
