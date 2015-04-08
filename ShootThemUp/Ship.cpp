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
Ship::Ship():_health(DEFAULT_SHIP_LIFE), _mainShoot(nullptr), _level(nullptr){}

/*
 * constructor
 * params : x, y and health of a ship
 */
Ship::Ship(const float x, const float y, const int health):GraphicElement(x, y), _health(health), _mainShoot(nullptr){}

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
    
    _mainShoot = new Bullet(_x, _y + DEFAULT_SHIP_OFFSET_SHOOT, MAIN_SHOOT_DAMAGE);
    _level->addBullet(_mainShoot);
    
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