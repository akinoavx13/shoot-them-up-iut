//
//  Ship.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Ship.h"
#include "Level.h"
#include "const.h"

using namespace std;

/*
 * default constructor
 */
Ship::Ship():_health(DEFAULT_SHIP_LIFE), _mainShoot(nullptr), _level(nullptr), _damage(MAIN_SHOOT_DAMAGE), _bulletType(0), _fireRate(ENEMY_FIRERATE) {}

/*
 * constructor
 * params : x, y and health of a ship
 */
Ship::Ship(const float x, const float y, const int health, const int width, const int height, const float fireRate):GraphicElement(x, y, width, height, ENEMY_DEFAULT_SPEEDX, ENEMY_DEFAULT_SPEEDY), _health(health), _mainShoot(nullptr), _bulletType(0), _level(nullptr), _damage(MAIN_SHOOT_DAMAGE), _fireRate(ENEMY_FIRERATE) {}

Ship::Ship(const float x, const float y, const int health, const int width, const int height, const float fireRate, const int speedX, const int speedY):GraphicElement(x, y, width, height, speedX, speedY), _health(health), _mainShoot(nullptr), _bulletType(0), _level(nullptr), _damage(MAIN_SHOOT_DAMAGE), _fireRate(ENEMY_FIRERATE) {}


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
        _mainShoot = new Bullet(_x+(_width/2)-(FIREBALL_PICTURE_WIDTH/2), _y-FIREBALL_PICTURE_HEIGHT-5, MAIN_SHOOT_DAMAGE, STANDARD_LASER_PICTURE_WIDTH, STANDARD_LASER_PICTURE_HEIGHT, ALLY_DEFAULT_SPEEDX, ALLY_DEFAULT_SPEEDY);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 1){
        _mainShoot = Bullet::FireBall(_x+(_width/2)+(FIREBALL_PICTURE_WIDTH/2), _y-FIREBALL_PICTURE_HEIGHT-5);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 2){
        _mainShoot = Bullet::TinyLaser(_x+(_width/2)+(TINY_PICTURE_WIDTH/2), _y-TINY_PICTURE_HEIGHT-5);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 3){
        _mainShoot = Bullet::Laser(_x+(_width/2)+(LITTLE_LASER_PICTURE_WIDTH/2), _y-LITTLE_LASER_PICTURE_HEIGHT-5);
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
    str = "\tCadence de tire : " + to_string(_fireRate) + "\n";
    str += GraphicElement::toString();

    return str;
}

void Ship::move(const float x, const float y){
    if (x >= 0 && x+_width < MODEL_WIDTH) {
        _x = x;
    }else{
        //cout << "X n'est pas compris entre 0 et " << MODEL_WIDTH << ". X vaut : " << x << endl;
    }

    if (y >= 0 && y+_height < MODEL_HEIGHT) {
        _y = y;
    }else{
        //cout << "Y n'est pas compris entre 0 et " << MODEL_HEIGHT << ". Y vaut : " << y << endl;
    }
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

float Ship::getFireRate() const{
    return _fireRate;
}
