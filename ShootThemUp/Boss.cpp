//
//  Boss.cpp
//  ShootThemUp
//
//  Created by Nicolas on 30/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Boss.h"

using namespace std;

/*
 * CONSTRUCTOR
 */
Boss::Boss() {}

Boss::Boss(const float x, const float y, const int health, const float firerate):Enemy(x, y, health, 0, BOSS_PICTURE_WIDTH/3, BOSS_PICTURE_HEIGHT, firerate) {}

/*
 * DESTRUCTOR
 */
Boss::~Boss(){}

/*
 * METHODS
 */
//write some informations about boss
string Boss::toString() const{
    string str = "Un boss";

    str += "\n";
    str += Ship::toString();
    str += "\n";

    return str;
}