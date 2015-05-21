//
//  Bullet.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 21/03/2015.
//  Copyright (c) 2015 Nicolas Valaise. All rights reserved.
//

#include "Bullet.h"

using namespace std;

/*
 * CONSTRUCTOR
 */
Bullet::Bullet():_damage(STANDARD_DAMAGE), _state(0), _price(0), _owner("ally"){}

Bullet::Bullet(const float x, const float y, const int damage, const int width, const int height, const float speedX, const float speedY, const int type, const int price, std::string owner) : GraphicElement(x, y, width, height, speedX, speedY), _damage(damage), _type(type), _state(0), _price(price), _owner(owner){}

Bullet* Bullet::FireBall(const float x, const float y, const float speedX, const float speedY, const float damage, std::string owner){
    Bullet* bullet = new Bullet(x, y, damage, FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT,speedX,speedY, 1, FIREBALL_PRICE, owner);
    return bullet;
}

Bullet* Bullet::TinyLaser(const float x, const float y, const float speedX, const float speedY, const float damage, std::string owner){
    Bullet* bullet = new Bullet(x, y, damage, TINYLASER_PICTURE_WIDTH, TINYLASER_PICTURE_HEIGHT,speedX,speedY, 2, TINYLASER_PRICE, owner);
    return bullet;
}

Bullet* Bullet::Laser(const float x, const float y, const float speedX, const float speedY, const float damage, std::string owner){
    Bullet* bullet = new Bullet(x, y, damage, LASER_PICTURE_WIDTH, LASER_PICTURE_HEIGHT,speedX,speedY, 3, LASER_PRICE, owner);
    return bullet;
}

Bullet* Bullet::DoubleTinyLaser(const float x, const float y, const float speedX, const float speedY, const float damage, std::string owner){
    Bullet* bullet = new Bullet(x, y, damage, DOUBLE_TINY_LASER_PICTURE_WIDTH, DOUBLE_TINY_LASER_PICTURE_HEIGHT,speedX,speedY, 4, DOUBLE_TINY_LASER_PRICE, owner);
    return bullet;
}

/*
 * DESTRUCTOR
 */
Bullet::~Bullet(){

}

/*
 * METHODS
 */
//write some informations about bullet
string Bullet::toString() const{
    string str = "Une balle";

    str += "\n";
    str += GraphicElement::toString();
    #ifdef __linux__
    str += "Dommage : " + to_string(_damage) + "\n";
    #endif
    str += "\n";

    return str;
}

//upgrad the bullet
bool Bullet::improve(){
    if(_state<5){
        _state++;
        _damage += _state * 10;
        return true;
    }
    return false;
}

//increase the price of one bullet
void Bullet::growPrice(){
    _price += 70;
}

//move the bullet to x and y position
void Bullet::move(const float x, const float y){
    _y = y;
    _x = x;
}

/*
 * GETTERS
 */
int Bullet::getDamage() const{
    return _damage;
}

int Bullet::getType() const{
    return _type;
}

int Bullet::getState() const{
    return _state;
}

int Bullet::getPrice() const{
    return _price;
}

string Bullet::getOwner() const{
    return _owner;
}

/*
 * SETTERS
 */
void Bullet::setPrice(int price){
    _price=price;
}