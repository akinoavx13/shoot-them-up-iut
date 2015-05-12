//
//  Ally.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Ally.h"
#include "Level.h"

using namespace std;

/*
 * default constructor
 */
Ally::Ally() : Ship(MODEL_WIDTH/2, MODEL_HEIGHT-ALLY_PICTURE_HEIGHT-10, ALLY_LIFE,ALLY_PICTURE_WIDTH/3, ALLY_PICTURE_HEIGHT, ALLY_FIRERATE, ALLY_SPEEDX, ALLY_SPEEDY), _numbersOfLife(ALLY_NUMBER_OF_LIFE), _score(DEFAULT_SCORE), _numberShootWithBonus(0), _numberShootWithBonusMax(4)
{
    _othersBullets.push_back(_mainShoot);
    
    Bullet * newBullet2 = Bullet::FireBall(_x + _width / 2 - FIREBALL_PICTURE_WIDTH / 2, _y - FIREBALL_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, FIREBALL_DAMAGE);
    
    _othersBullets.push_back(newBullet2);
    
    Bullet * newBullet3 = Bullet::TinyLaser(_x + _width / 2 - TINYLASER_PICTURE_WIDTH / 2, _y - TINYLASER_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, TINY_DAMAGE);
    
    _othersBullets.push_back(newBullet3);
    
    Bullet * newBullet4 = Bullet::Laser(_x + _width / 2 - LASER_PICTURE_WIDTH / 2, _y - LASER_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, LASER_DAMAGE);
    
    _othersBullets.push_back(newBullet4);
    
    Bullet * newBullet5 = Bullet::DoubleTinyLaser(_x + _width / 2 - DOUBLE_TINY_LASER_PICTURE_WIDTH / 2, _y - DOUBLE_TINY_LASER_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, DOUBLE_TINY_LASER_DAMAGE);
    
    _othersBullets.push_back(newBullet5);
    
    _bonusShoot = newBullet2;
}

void Ally::bonusShoot(){
    if(_numberShootWithBonus<_numberShootWithBonusMax)
    {
        int width = _bonusShoot->getWidth();
        int height = _bonusShoot->getHeight();
    
        int x = _x + _width/2 - width/2;
        int y = _y - height - 5;
    
    
        Bullet * copieBonus = new Bullet(x, y, _bonusShoot->getDamage(), width, height, _bonusShoot->getSpeedX(), _bonusShoot->getSpeedY(), 0);
        _level->addBullet(copieBonus);
    
        _numberShootWithBonus++;
    }
}

void Ally::resetBonus(){
    _numberShootWithBonus=0;
    if(_numberShootWithBonusMax<20){
        _numberShootWithBonusMax+=2;
    }
}

/*
 * contructor
 * params : x, y and health of ally
 */
//Ally::Ally(const float x, const float y, const int health):Ship(x, y, health,ALLY_PICTURE_HEIGHT, ALLY_PICTURE_WIDTH/3), _numbersOfLife(DEFAULT_NUMBER_OF_LIFE), _score(DEFAULT_SCORE) {}

/*
 * destructor
 * info : virtual
 */
Ally::~Ally(){
    for(int i = 0; i<_othersBullets.size(); i++){
        delete _othersBullets[i];
    }
    _othersBullets.clear();
}

//----------METHODS----------
/*
 * returns : true if the player has more life
 * info : constant
 */
bool Ally::isOver() const{
    return _numbersOfLife <= 0;
}

/*
 * returns : string of number life and ship toString
 * info : constant, override
 */
string Ally::toString() const{
    string str = "Notre vaisseau";
    str += "\n";

    str += "\tScore : ";
    #ifdef __linux__
    str += to_string(_score) + "\n";
    #endif

    str += "\tNombre de vie : ";
    #ifdef __linux__
    str += to_string(_numbersOfLife);
    #endif

    str += "\n";

    str += "\tType de missile : ";
    if(_bulletType == 0){
        str += "standard";
    }
    else if(_bulletType == 1){
        str += "boule de feu";
    }
    else if(_bulletType == 2){
        str += "petit laser";
    }
    else if(_bulletType == 3){
        str += "laser";
    }
    str += "\n";

    str += "\tDégat : ";
    if(_bulletType == 0){
    #ifdef __linux__
        str += to_string(STANDARD_DAMAGE);
    #endif

    }
    else if(_bulletType == 1){
    #ifdef __linux__
        str += to_string(FIREBALL_DAMAGE);
    #endif

    }
    else if(_bulletType == 2){
    #ifdef __linux__
        str += to_string(TINYLASER_DAMAGE);
    #endif

    }
    else if(_bulletType == 3){
    #ifdef __linux__
        str += to_string(LASER_DAMAGE);
    #endif

    }

    str += "\n";

    str += Ship::toString();
    return str;
}

//----------GETTERS----------
/*
 * returns : number of life
 * info : constant
 */
int Ally::getNumberOfLife() const{
    return _numbersOfLife;
}

int Ally::getScore() const{
    return _score;
}

int Ally::getNumberShootBonus() const{
    return _numberShootWithBonus;
}

int Ally::getNumberShootBonusMax() const{
    return _numberShootWithBonusMax;
}

//----------SETTERS----------
/*
 * set the health of ally
 */

/*
 * set number of life
 */
void Ally::setNumberOfLife(int numberOfLive){
    _numbersOfLife = numberOfLive;
}

void Ally::setScore(int expPoint){
    _score += DEFAULT_POINT + expPoint;
}