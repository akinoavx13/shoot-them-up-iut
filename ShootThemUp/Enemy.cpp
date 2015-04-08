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

/*
 * an enemy can shoot
 * info : override
 */
void Enemy::shoot(){
    
    _mainShoot = new Bullet(_x, _y - DEFAULT_SHIP_OFFSET_SHOOT, MAIN_SHOOT_DAMAGE);
    _level->addBullet(_mainShoot);
    
}