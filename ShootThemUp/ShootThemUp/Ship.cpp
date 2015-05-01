//
//  Ship.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Ship.h"
#include "Level.h"

using namespace std;

/*
 * default constructor
 */
Ship::Ship():_health(DEFAULT_SHIP_LIFE), _mainShoot(nullptr), _level(nullptr), _damage(MAIN_SHOOT_DAMAGE), _bulletType(0){}

/*
 * constructor
 * params : x, y and health of a ship
 */
Ship::Ship(const float x, const float y, const int health):GraphicElement(x, y), _health(health), _mainShoot(nullptr), _bulletType(0), _level(nullptr), _damage(MAIN_SHOOT_DAMAGE){}


/*
 * destructor
 * info : virtual, abstract
 */
Ship::~Ship(){

    //la destruction des balles se fait dans le level quand il y a une collisions
}

//----------METHODS----------
/*
 * shoot. Create a new bullet and add it in the bullet's vector in level
 */
void Ship::shoot(){
    if(_bulletType == 0){
        _mainShoot = new Bullet(_x, _y + DEFAULT_SHIP_OFFSET_SHOOT, MAIN_SHOOT_DAMAGE);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 1){
        _mainShoot = Bullet::FireBall(_x, _y + DEFAULT_SHIP_OFFSET_SHOOT);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 2){
        _mainShoot = Bullet::TinyLaser(_x, _y + DEFAULT_SHIP_OFFSET_SHOOT);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 3){
        _mainShoot = Bullet::Laser(_x, _y + DEFAULT_SHIP_OFFSET_SHOOT);
        _level->addBullet(_mainShoot);
    }
}

/*
 * returns : string, toString of graphic element and health points
 * info : constant, virtual, override
 */
string Ship::toString() const{

    string str;

    str = "\tPoints de vie : " + to_string(_health) + "\n";

    str += GraphicElement::toString();

    return str;
}

/*
 * returns : true if there is a collision between ship and a graphic element
 * info : constant
 */
bool Ship::collisions(GraphicElement* graphicElement)const{

    if(
       (_x >= graphicElement->getX() && _x <= graphicElement->getX() + graphicElement->getWidth() && _y >= graphicElement->getY() && _y <= graphicElement->getY() + graphicElement->getHeight()) ||
       (_x + _width >= graphicElement->getX() && _x + _width <= graphicElement->getX() + graphicElement->getWidth() && _y >= graphicElement->getY() && _y <= graphicElement->getY() + graphicElement->getHeight()) ||
       (_x >= graphicElement->getX() && _x <= graphicElement->getX() + graphicElement->getWidth() && _y + _height >= graphicElement->getY() && _y + _height <= graphicElement->getY() + graphicElement->getHeight()) ||
       (_x + _width >= graphicElement->getX() && _x + _width <= graphicElement->getX() + graphicElement->getWidth() && _y + _height >= graphicElement->getY() && _y + _height <= graphicElement->getY() + graphicElement->getHeight())
    ){
        return true;
    }
    return false;

}

/*
 * returns : true if health <= 0
 */
bool Ship::isDead(){
    return _health <= 0;
}

//----------GETTERS----------
/*
 * returns : health
 * info : constant
 */
int Ship::getHealth() const{
    return _health;
}

int Ship::getBulletType() const{
    return _bulletType;
}

int Ship::getDamage() const{
    return _damage;
}


//----------SETTERS----------
/*
 * set the level
 */
void Ship::setLevel(Level* level){
    _level = level;
}

/*
 * set health
 */
void Ship::setHealth(int health){
    _health = health;
}

void Ship::setBulletType(int bulletType){
    _bulletType = bulletType;
}

void Ship::setDamage(int damage){
    _damage = damage;
}
