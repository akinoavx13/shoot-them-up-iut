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

#include "../ShootThemUp/Ally.h"
#include "../ShootThemUp/Level.h"
#include "../ShootThemUp/Enemy.h"
#include "../ShootThemUp/Boss.h"

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

//check if the player haven't life points
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
