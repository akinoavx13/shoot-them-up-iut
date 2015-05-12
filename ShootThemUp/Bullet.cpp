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
 * default constructor
 */
Bullet::Bullet():_damage(STANDARD_DAMAGE){}

/*
 * constructor
 * params : x, y and damage of a bullet
 */
Bullet::Bullet(const float x, const float y, const int damage, const int width, const int height, const float speedX, const float speedY, const int type) : GraphicElement(x, y, width, height, speedX, speedY), _damage(damage), _type(type), _state(0){}

Bullet* Bullet::FireBall(const float x, const float y, const float speedX, const float speedY, const float damage){
    Bullet* bullet = new Bullet(x, y, damage, FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT,speedX,speedY, 1);
    return bullet;
}

Bullet* Bullet::TinyLaser(const float x, const float y, const float speedX, const float speedY, const float damage){
    Bullet* bullet = new Bullet(x, y, damage, TINYLASER_PICTURE_WIDTH, TINYLASER_PICTURE_HEIGHT,speedX,speedY, 2);
    return bullet;
}

Bullet* Bullet::Laser(const float x, const float y, const float speedX, const float speedY, const float damage){
    Bullet* bullet = new Bullet(x, y, damage, LASER_PICTURE_WIDTH, LASER_PICTURE_HEIGHT,speedX,speedY, 3);
    return bullet;
}

Bullet* Bullet::DoubleTinyLaser(const float x, const float y, const float speedX, const float speedY, const float damage){
    Bullet* bullet = new Bullet(x, y, damage, DOUBLE_TINY_LASER_PICTURE_WIDTH, DOUBLE_TINY_LASER_PICTURE_HEIGHT,speedX,speedY, 4);
    return bullet;
}

/*
 * destructor
 * info : virtual
 */
Bullet::~Bullet(){

}

//----------METHODS----------
/*
 * returns : string, graphic element toString and damage
 */
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

void Bullet::improve(){
    if(_state<5){
        _state++;
        _damage+=_state*10;
    }
}

//----------GETTERS----------
/*
 * get damage
 * info : constant
 */
int Bullet::getDamage() const{
    return _damage;
}

void Bullet::move(const float x, const float y){
    _y = y;
    _x = x;
}

int Bullet::getType() const{
    return _type;
}
