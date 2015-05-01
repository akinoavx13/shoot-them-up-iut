//
//  Enemy.h
//  ShootThemUp
//
//  Created by Nicolas Valaise on 18/03/2015.
//  Copyright (c) 2015 Nicolas Valaise. All rights reserved.
//

#include "Enemy.h"
#include "Level.h"

using namespace std;

/*
 * default constructor
 */
Enemy::Enemy(){}

/*
 * constructor
 * params : x, y ans health of enemy
 */
Enemy::Enemy(const float x, const float y, const int health, const int type, int width, int height):Ship(x, y, health, width, height, DEFAULT_SHIP_FIRERATE), _type(type) {}

Enemy* Enemy::Tiny(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, DEFAULT_TINY_LIFE, 1, TINY_PICTURE_WIDTH/3, TINY_PICTURE_HEIGHT);
    enemy->_damage = DEFAULT_TINY_DAMAGE;
    return enemy;
}

Enemy* Enemy::Submarine(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, DEFAULT_SUBMARINE_LIFE, 2, SUBMARINE_PICTURE_WIDTH/2, SUBMARINE_PICTURE_HEIGHT);
    enemy->_damage = DEFAULT_SUBMARINE_DAMAGE;
    return enemy;
}

Enemy* Enemy::Mighty(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, DEFAULT_MIGHTY_LIFE, 3, MIGHTY_PICTURE_WIDTH/3, MIGHTY_PICTURE_HEIGHT);
    enemy->_damage = DEFAULT_MIGHTY_DAMAGE;
    return enemy;
}

/*
 * destructor
 * info : virtual
 */
Enemy::~Enemy(){

    cout << "Enemy delete" << endl;

}

//----------METHODS----------
/*
 * returns : string, ship toString
 * info : constant, override
 */
string Enemy::toString() const{
    string str = "Un ennemi";

    str += "\n";
    str += Ship::toString();
    str += "\n";

    return str;
}

void Enemy::shoot(){
    _mainShoot = new Bullet(_x+(_width/2)-(FIREBALL_PICTURE_HEIGHT/2), _y +_height+5, _damage, _width, _height,BULLET_DEFAULT_SPEEDX,BULLET_DEFAULT_SPEEDY);
    _level->addBullet(_mainShoot);
}

int Enemy::getType() const{
    return _type;
}
