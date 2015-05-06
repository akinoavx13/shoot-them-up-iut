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
Bullet::Bullet():_damage(DEFAULT_BULLET_DAMAGE){}

/*
 * constructor
 * params : x, y and damage of a bullet
 */
Bullet::Bullet(const float x, const float y, const int damage, const int width, const int height, const int speedX, const int speedY) : GraphicElement(x, y, width, height, speedX, speedY), _damage(damage){}

Bullet* Bullet::FireBall(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, DEFAULT_FIREBALL_DAMAGE, FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT,BULLET_DEFAULT_SPEEDX,BULLET_DEFAULT_SPEEDY);
    return bullet;
}

Bullet* Bullet::TinyLaser(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, DEFAULT_TINYLASER_DAMAGE, LITTLE_LASER_PICTURE_WIDTH, LITTLE_LASER_PICTURE_HEIGHT,BULLET_DEFAULT_SPEEDX,BULLET_DEFAULT_SPEEDY);
    return bullet;
}

Bullet* Bullet::Laser(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, DEFAULT_TINYLASER_DAMAGE, BIG_LASER_PICTURE_WIDTH, BIG_LASER_PICTURE_HEIGHT,BULLET_DEFAULT_SPEEDX,BULLET_DEFAULT_SPEEDY);
    return bullet;
}

/*
 * destructor
 * info : virtual
 */
Bullet::~Bullet(){

    //cout << "Bullet delete" << endl;

}

//----------METHODS----------
/*
 * returns : string, graphic element toString and damage
 */
string Bullet::toString() const{
    string str = "Une balle";

    str += "\n";
    str += GraphicElement::toString();
    str += "Dommage : " + to_string(_damage) + "\n";
    str += "\n";

    return str;
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
