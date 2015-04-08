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

#include "test.h"

BOOST_AUTO_TEST_CASE(addi){
    
    BOOST_CHECK(a() == 1);
    
}
