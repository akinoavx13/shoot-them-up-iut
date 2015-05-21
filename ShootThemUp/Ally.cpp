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
 * CONSTRUCTOR
 */
Ally::Ally() : Ship(MODEL_WIDTH / 2 - ALLY_PICTURE_WIDTH / 6, MODEL_HEIGHT - ALLY_PICTURE_HEIGHT - 25, ALLY_LIFE, ALLY_PICTURE_WIDTH / 3, ALLY_PICTURE_HEIGHT, ALLY_FIRERATE, ALLY_SPEEDX, ALLY_SPEEDY), _numbersOfLife(ALLY_NUMBER_OF_LIFE), _score(DEFAULT_SCORE), _numberShootWithBonus(0), _numberShootWithBonusMax(4), _numberLifeBuy(0), _name("")
{
    Bullet * newBullet1 = new Bullet(_x + _width / 2 - STANDARD_PICTURE_WIDTH / 2, _y - STANDARD_PICTURE_HEIGHT - 5, STANDARD_DAMAGE, STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, 0, STANDARD_PRICE, "ally");
    _othersBullets.push_back(newBullet1);

    Bullet * newBullet2 = Bullet::FireBall(_x + _width / 2 - FIREBALL_PICTURE_WIDTH / 2, _y - FIREBALL_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, FIREBALL_DAMAGE, "ally");

    _othersBullets.push_back(newBullet2);

    Bullet * newBullet3 = Bullet::TinyLaser(_x + _width / 2 - TINYLASER_PICTURE_WIDTH / 2, _y - TINYLASER_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, TINY_DAMAGE, "ally");

    _othersBullets.push_back(newBullet3);

    Bullet * newBullet4 = Bullet::DoubleTinyLaser(_x + _width / 2 - DOUBLE_TINY_LASER_PICTURE_WIDTH / 2, _y - DOUBLE_TINY_LASER_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, DOUBLE_TINY_LASER_DAMAGE, "ally");
    _othersBullets.push_back(newBullet4);

    Bullet * newBullet5 = Bullet::Laser(_x + _width / 2 - LASER_PICTURE_WIDTH / 2, _y - LASER_PICTURE_HEIGHT - 5, ALLY_BULLET_SPEEDX, ALLY_BULLET_SPEEDY, LASER_DAMAGE, "ally");

    _othersBullets.push_back(newBullet5);

    _bonusShoot = newBullet2;
}

/*
 * DESTRUCTOR
 */
Ally::~Ally(){
    for(int i = 0; i < _othersBullets.size(); i++){
        delete _othersBullets[i];
    }
    _othersBullets.clear();
}

/*
 * METHODS
 */

//allow to shoot the bonus shoot
bool Ally::bonusShoot(){
    
    if(_numberShootWithBonus<_numberShootWithBonusMax)
    {
        int width = _bonusShoot->getWidth();
        int height = _bonusShoot->getHeight();
        
        int x = _x + _width / 2 - width / 2;
        int y = _y - height - 5;
        
        Bullet * copieBonus = new Bullet(x, y, _bonusShoot->getDamage(), width, height, _bonusShoot->getSpeedX(), _bonusShoot->getSpeedY(), _bonusShoot->getType(), 0, "ally");
        
        _level->addBullet(copieBonus);
        _numberShootWithBonus++;
        
        return true;
    }
    return false;
}

//reset all bonus shoot
void Ally::resetBonus(){
    
    _numberShootWithBonus = 0;
    
    if(_numberShootWithBonusMax < 100){
        _numberShootWithBonusMax += 3;
    }
}

//return true if we have the money to buy this item
bool Ally::canBuyItem(int item) const{
    return _score - _othersBullets[item]->getPrice() >= 0;
}

//return true if the player didn't have life
bool Ally::isOver() const{
    return _numbersOfLife <= 0;
}

//change the bonus of the player
void Ally::changeBonus(int type){
    if(type<_othersBullets.size()){
        _bonusShoot = _othersBullets[type];
    }
}

//delete the last letter of player's name when he entrer his score
void Ally::deleteOneLetter(){
    if(_name.size() > 0){
        _name.erase(_name.size() - 1);
    }
}

//add player's letter
void Ally::addLetter(string letter){
    _name += letter;
}

//move the player to x and y position
void Ally::move(const float x, const float y){
    if (x >= 0 && x + _width < MODEL_WIDTH) {
        _x = x;
    }

    if (y >= 30 && y + _height < MODEL_HEIGHT) {
        _y = y;
    }
}

//write some informations on the players
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

//increase the performance of the bonus shoot. Return true is it's upgraded
bool Ally::improveOneBulletBonus(int type){
    if(_othersBullets.size() > type){
        if(_othersBullets[type]->improve()){
            return true;
        }
    }
    return false;
}

/*
 * GETTERS
 */

Bullet * Ally::getOneBulletBonus(int type) const{
    if(_othersBullets.size() > type){
        return _othersBullets[type];
    }
    return _othersBullets[0];
}

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

int Ally::getBulletBonusType() const{
    return _bonusShoot->getType();
}

int Ally::getMainBulletType() const{
    return _bulletType;
}

Bullet * Ally::getBulletBonus() const{
    return _bonusShoot;
}

string Ally::getName() const{
    return _name;
}

/*
 * SETTERS
 */
void Ally::setNumberOfLife(int numberOfLive){
    _numbersOfLife = numberOfLive;
}

void Ally::setScore(int expPoint){
    _score = DEFAULT_POINT + expPoint;
}

void Ally::reduceScore(int less){
    _score-=less;
}

void Ally::setNumberLifeBuy(int i){
    _numberLifeBuy = i;
}

int Ally::getNumberLifeBuy() const{
    return _numberLifeBuy;
}
