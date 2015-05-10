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
Bullet::Bullet(const float x, const float y, const int damage, const int width, const int height, const int speedX, const int speedY, const int type) : GraphicElement(x, y, width, height, speedX, speedY), _damage(damage), _type(type){}

Bullet* Bullet::FireBall(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, FIREBALL_DAMAGE, FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT,ALLY_BULLET_SPEEDX,ALLY_BULLET_SPEEDY, 1);
    return bullet;
}

Bullet* Bullet::TinyLaser(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, TINYLASER_DAMAGE, TINYLASER_PICTURE_WIDTH, TINYLASER_PICTURE_HEIGHT,ALLY_BULLET_SPEEDX,ALLY_BULLET_SPEEDY, 2);
    return bullet;
}

Bullet* Bullet::Laser(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, LASER_DAMAGE, LASER_PICTURE_WIDTH, LASER_PICTURE_HEIGHT,ALLY_BULLET_SPEEDX,ALLY_BULLET_SPEEDY, 3);
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
    #ifdef __linux__
    str += "Dommage : " + to_string(_damage) + "\n";
    #endif
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

int Bullet::getType() const{
    return _type;
}
