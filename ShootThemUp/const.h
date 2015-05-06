//
//  const.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __CONST_H__
#define __CONST_H__

#include <string>

//windows
const int MODEL_WIDTH = 500;
const int MODEL_HEIGHT = 500;

//bullet
const int DEFAULT_BULLET_DAMAGE = 10;

//level
const int DEFAULT_LEVEL_NUMBER = 1;
const int DEFAULT_LEVEL_ENEMY_NUMBER = 3;
const int DEFAULT_LEVEL_INITIAL_ENEMY_OFFSET = 50;

//graphic element
const float DEFAULT_GRAPHIC_ELEMENT_X = 0;
const float DEFAULT_GRAPHIC_ELEMENT_Y = 0;
const float DEFAULT_GRAPHIC_ELEMENT_SPEED_X = 1;
const float DEFAULT_GRAPHIC_ELEMENT_SPEED_Y = 1;
const int DEFAULT_GRAPHIC_ELEMENT_WIDTH = 10;
const int DEFAULT_GRAPHIC_ELEMENT_HEIGHT = 10;

//ship
const int DEFAULT_SHIP_LIFE = 100;
const int DEFAULT_SHIP_OFFSET_SHOOT = 20;
const int DEFAULT_SHIP_FIRERATE = 1.5;

//shoot
const int MAIN_SHOOT_DAMAGE = 20;

//player
const int DEFAULT_NUMBER_OF_LIFE = 3;
const int DEFAULT_SCORE = 0;
const int DEFAULT_POINT = 20;

//TINY
const int DEFAULT_TINY_LIFE = 70;
const int DEFAULT_TINY_DAMAGE = 20;

//SUBMARINE
const int DEFAULT_SUBMARINE_LIFE = 150;
const int DEFAULT_SUBMARINE_DAMAGE = 40;

//MIGHTY
const int DEFAULT_MIGHTY_LIFE = 110;
const int DEFAULT_MIGHTY_DAMAGE = 50;

//FIREBALL
const int DEFAULT_FIREBALL_DAMAGE = 30;
const int DEFAULT_FIREBALL_PRICE = 200;

//TINYLASER
const int DEFAULT_TINYLASER_DAMAGE = 50;
const int DEFAULT_TINYLASER_PRICE = 400;

//LASER
const int DEFAULT_LASER_DAMAGE = 100;
const int DEFAULT_LASER_PRICE = 700;

//RESTAURE LIFE
const int DEFAULT_RESTRAURE_LIFE_PRICE = 300;

//ADD LIFE
const int DEFAULT_ADD_LIFE_PRICE = 400;

//SCORE
const std::string LINUX_SCORE_FILE = "ShootThemUp/score.txt" ;
const std::string MAC_SCORE_FILE_NICOLAS = "/Users/nicolas/Desktop/ShootThemUp/ShootThemUp/score.txt";
const std::string MAC_SCORE_FILE_MAXIME = "/Users/Maxime/Desktop/Shump/ShootThemUp/ShootThemUp/score.txt";

const std::string YOU_FILE = LINUX_SCORE_FILE; //please, change hear the constancy to execute the code

/**
    FOR THE VIEW
**/

//ALLY
const int ALLY_PICTURE_HEIGHT = 49;
const int ALLY_PICTURE_WIDTH = 183;

const int ALLY_DEFAULT_SPEEDX = 0;
const int ALLY_DEFAULT_SPEEDY = -6;

//ENNEMY
const int SUBMARINE_PICTURE_HEIGHT = 197;
const int SUBMARINE_PICTURE_WIDTH = 82;

const int TINY_PICTURE_HEIGHT = 31;
const int TINY_PICTURE_WIDTH = 96;

const int MIGHTY_PICTURE_HEIGHT = 45;
const int MIGHTY_PICTURE_WIDTH = 180;

const int ENEMY_DEFAULT_SPEEDX = 5;
const int ENEMY_DEFAULT_SPEEDY = 5;

//BOSS
const int BOOS_PICTURE_HEIGHT = 74;
const int BOSS_PICTURE_WIDTH = 279;

const int BOSS_DEFAULT_SPEEDX = 7;
const int BOSS_DEFAULT_SPEEDY = 7;

//BULLETS
const int DUBBLE_LASER_PICTURE_HEIGHT = 16;
const int DUBBLE_LASER_PICTURE_WIDTH = 17;

const int FIREBALL_PICTURE_HEIGHT = 9;
const int FIREBALL_PICTURE_WIDTH = 9;

const int BIG_LASER_PICTURE_HEIGHT = 30;
const int BIG_LASER_PICTURE_WIDTH = 9;

const int LITTLE_LASER_PICTURE_HEIGHT = 9;
const int LITTLE_LASER_PICTURE_WIDTH = 9;

const int STANDARD_LASER_PICTURE_HEIGHT = 9;
const int STANDARD_LASER_PICTURE_WIDTH = 9;

const int BULLET_DEFAULT_SPEEDX = 0;
const int BULLET_DEFAULT_SPEEDY = 9;


#endif
