//
//  Ship.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__Ship__
#define __ShootThemUp__Ship__

#include <stdio.h>
#include <string>
#include <iostream>

#include "GraphicElement.h"
#include "const.h"
#include "Bullet.h"

class Level;

class Ship : public GraphicElement{
protected:

    int _health;
    Bullet* _mainShoot;
    int _bulletType;
    Level* _level;
    int _damage;

    float _fireRate;

public:

    //CONSTRUCTOR
    Ship();
    Ship(const float x, const float y, const int health, const int width, const int height, const float fireRate);
    Ship(const float x, const float y, const int health, const int width, const int height, const float fireRate, const int speedX, const int speedY);
    //DESTRUCTOR
    virtual ~Ship() = 0;

    //METHODS
    virtual void shoot();
    virtual std::string toString() const override;
    virtual void move(const float x, const float y) override;

    bool isDead();

    //GETTERS
    int getHealth() const;
    int getBulletType() const;
    int getDamage() const;
    float getFireRate() const;

    //SETTERS
    void setLevel(Level* level);
    void setHealth(int health);
    void setBulletType(int bulletType);
    void setDamage(int damage);

};

#endif /* defined(__ShootThemUp__Ship__) */
