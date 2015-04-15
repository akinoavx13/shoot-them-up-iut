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

BOOST_AUTO_TEST_CASE(alive){
    Ally a;

    BOOST_CHECK(a.isDead() == false);

}

BOOST_AUTO_TEST_CASE(dead){
    Ally a;
    a.setNumberOfLife(0);

    BOOST_CHECK(a.isOver() == true);
}

BOOST_AUTO_TEST_CASE(loseLife){
    Ally a;
    a.setHealth(0);

    BOOST_CHECK(a.isDead() == true);
}
