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
 * destructor
 * info : virtual
 */
Enemy::~Enemy(){

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
    
    if(_bulletType == 0){
        _mainShoot = new Bullet(_x + _width / 2 - STANDARD_PICTURE_WIDTH / 2, _y + STANDARD_PICTURE_HEIGHT + 5 + _height, _damage, STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, 0);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 1){
        _mainShoot = Bullet::FireBall(_x + _width / 2 - FIREBALL_PICTURE_WIDTH / 2, _y + FIREBALL_PICTURE_HEIGHT + 5 + _height, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, _damage);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 2){
        _mainShoot = Bullet::TinyLaser(_x + _width / 2 - TINYLASER_PICTURE_WIDTH / 2, _y + TINYLASER_PICTURE_HEIGHT + 5 + _height, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, _damage);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 3){
        _mainShoot = Bullet::Laser(_x + _width / 2 - LASER_PICTURE_WIDTH / 2, _y + LASER_PICTURE_HEIGHT + 5 + _height, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, _damage);
        _level->addBullet(_mainShoot);
    }
    
    /*
        _mainShoot = new Bullet(_x + _width / 2 - STANDARD_PICTURE_HEIGHT / 2, _y + _height + 5, _damage, STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, ENEMY_BULLET_SPEEDX, ENEMY_BULLET_SPEEDY, 0);
        _level->addBullet(_mainShoot);
    */
}

void Enemy::shoot(const float x, const float y, const float speedX, const float speedY){
    if(_bulletType == 0){
        _mainShoot = new Bullet(x, y, _damage, STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, speedX, speedY, 0);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 1){
        _mainShoot = Bullet::FireBall(x, y, speedX, speedY, _damage);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 2){
        _mainShoot = Bullet::TinyLaser(x, y, speedX, speedY, _damage);
        _level->addBullet(_mainShoot);
    }
    else if(_bulletType == 3){
        _mainShoot = Bullet::Laser(x, y, speedX, speedY, _damage);
        _level->addBullet(_mainShoot);
    }
}
void Enemy::move(const float x, const float y){
    if (x >= 0 && x+_width < SCREEN_WIDTH - _width) {
        _x = x;
    }else{
        //cout << "X n'est pas compris entre 0 et " << MODEL_WIDTH << ". X vaut : " << x << endl;
    }

    if (y+_height < SCREEN_HEIGHT) {
        _y = y;
    }else{
        //cout << "Y n'est pas compris entre 0 et " << MODEL_HEIGHT << ". Y vaut : " << y << endl;
    }
}

int Enemy::getType() const{
    return _type;
}
