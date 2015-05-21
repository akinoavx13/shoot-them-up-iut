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
 * CONSTRUCTOR
 */
Enemy::Enemy(){}

Enemy::Enemy(const float x, const float y, const int health, const int type, const int width, const int height):Ship(x, y, health, width, height, ENEMY_FIRERATE, ENEMY_SPEEDX, ENEMY_SPEEDY), _type(type) {}

Enemy::Enemy(const float x, const float y, const int health, const int type, const int width, const int height, const float firerate):Ship(x, y, health, width, height, firerate, ENEMY_SPEEDX, ENEMY_SPEEDY), _type(type) {}

Enemy* Enemy::Tiny(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, TINY_LIFE, 1, TINY_PICTURE_WIDTH/3, TINY_PICTURE_HEIGHT);
    enemy->_damage = TINY_DAMAGE;
    return enemy;
}

Enemy* Enemy::Submarine(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, SUBMARINE_LIFE, 2, SUBMARINE_PICTURE_WIDTH/2, SUBMARINE_PICTURE_HEIGHT);
    enemy->_damage = SUBMARINE_DAMAGE;
    return enemy;
}

Enemy* Enemy::Mighty(const float x, const float y){
    Enemy* enemy = new Enemy(x, y, MIGHTY_LIFE, 3, MIGHTY_PICTURE_WIDTH/3, MIGHTY_PICTURE_HEIGHT);
    enemy->_damage = MIGHTY_DAMAGE;
    return enemy;
}

/*
 * DESTRUCTOR
 */
Enemy::~Enemy(){

}

/*
 * METHODS
 */
string Enemy::toString() const{
    
    string str = "Un ennemi";

    str += "\n";
    str += Ship::toString();
    str += "\n";

    return str;
}

//allow to shoot bullet in function of the enemy's bullet type
void Enemy::shoot(){
    
    if(_bulletType == 0){
        _mainShoot = new Bullet(_x + _width / 2 - STANDARD_PICTURE_WIDTH / 2, _y + STANDARD_PICTURE_HEIGHT + 5 + _height, _damage, STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, 0, STANDARD_PRICE, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 1){
        _mainShoot = Bullet::FireBall(_x + _width / 2 - FIREBALL_PICTURE_WIDTH / 2, _y + FIREBALL_PICTURE_HEIGHT + 5 + _height, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 2){
        _mainShoot = Bullet::TinyLaser(_x + _width / 2 - TINYLASER_PICTURE_WIDTH / 2, _y + TINYLASER_PICTURE_HEIGHT + 5 + _height, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 3){
        _mainShoot = Bullet::Laser(_x + _width / 2 - LASER_PICTURE_WIDTH / 2, _y + LASER_PICTURE_HEIGHT + 5 + _height, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 4){
        _mainShoot = Bullet::DoubleTinyLaser(_x + _width / 2 - DOUBLE_TINY_LASER_PICTURE_WIDTH / 2, _y + DOUBLE_TINY_LASER_PICTURE_HEIGHT + 5 + _height, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
}

//allow to shoot bullet in function of the enemy's bullet type
void Enemy::shoot(const float x, const float y, const float speedX, const float speedY){
    
    if(_bulletType == 0){
        _mainShoot = new Bullet(x, y, _damage, STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, speedX, speedY, 0, STANDARD_PRICE, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 1){
        _mainShoot = Bullet::FireBall(x, y, speedX, speedY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 2){
        _mainShoot = Bullet::TinyLaser(x, y, speedX, speedY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 3){
        _mainShoot = Bullet::Laser(x, y, speedX, speedY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 4){
        _mainShoot = Bullet::DoubleTinyLaser(x, y, speedX, speedY, _damage, "enemy");
        _level->addBullet(_mainShoot);
    }
}

//move enemy
void Enemy::move(const float x, const float y){
    _x = x;
    _y = y;
}

/*
 * GETTERS
 */
int Enemy::getType() const{
    return _type;
}

