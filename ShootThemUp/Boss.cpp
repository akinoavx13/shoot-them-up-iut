//
//  Boss.cpp
//  ShootThemUp
//
//  Created by Nicolas on 30/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Boss.h"

using namespace std;

Boss::Boss() {}

Boss::Boss(const float x, const float y, const int health):Enemy(x, y, health, 0, BOSS_PICTURE_WIDTH, BOSS_PICTURE_HEIGHT) {}

Boss::~Boss(){

    cout << "Boss delete" << endl;

}

string Boss::toString() const{
    string str = "Un boss";

    str += "\n";
    str += Ship::toString();
    str += "\n";

    return str;
}
