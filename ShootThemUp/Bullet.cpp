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
Bullet::Bullet(const float x, const float y, const int damage) : GraphicElement(x, y), _damage(damage){}

Bullet* Bullet::FireBall(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, DEFAULT_FIREBALL_DAMAGE);
    return bullet;
}

Bullet* Bullet::TinyLaser(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, DEFAULT_TINYLASER_DAMAGE);
    return bullet;
}

Bullet* Bullet::Laser(const float x, const float y){
    Bullet* bullet = new Bullet(x, y, DEFAULT_TINYLASER_DAMAGE);
    return bullet;
}

/*
 * destructor
 * info : virtual
 */
Bullet::~Bullet(){

    cout << "Bullet delete" << endl;

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
