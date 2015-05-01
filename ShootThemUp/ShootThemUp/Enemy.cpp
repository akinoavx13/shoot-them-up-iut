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
Enemy::Enemy(const float x, const float y, const int health):Ship(x, y, health){}


Enemy* Enemy::Tiny(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, DEFAULT_TINY_LIFE);
    enemy->_damage = DEFAULT_TINY_DAMAGE;
    return enemy;
}

Enemy* Enemy::Submarine(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, DEFAULT_SUBMARINE_LIFE);
    enemy->_damage = DEFAULT_SUBMARINE_DAMAGE;
    return enemy;
}

Enemy* Enemy::Mighty(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, DEFAULT_MIGHTY_LIFE);
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
    _mainShoot = new Bullet(_x, _y - DEFAULT_SHIP_OFFSET_SHOOT, _damage);
    _level->addBullet(_mainShoot);
}
