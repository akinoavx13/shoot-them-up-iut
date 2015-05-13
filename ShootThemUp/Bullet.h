//
//  Bullet.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 21/03/2015.
//  Copyright (c) 2015 Nicolas Valaise. All rights reserved.
//

#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <string>
#include <iostream>

#include "GraphicElement.h"
#include "const.h"

class Bullet : public GraphicElement {

private:
    int _damage;
    int _type;

    int _state;
    int _price;
public:
    //CONSTRUCTOR
    Bullet();
    Bullet(const float x, const float y, const int damage, const int width, const int height, const float speedX, const float speedY, const int type, const int price);
    static Bullet* FireBall(const float x, const float y, const float speedX, const float speedY, const float damage);
    static Bullet* TinyLaser(const float x, const float y, const float speedX, const float speedY, const float damage);
    static Bullet* Laser(const float x, const float y, const float speedX, const float speedY, const float damage);
    static Bullet* DoubleTinyLaser(const float x, const float y, const float speedX, const float speedY, const float damage);

    //DESTRUCTOR
    virtual ~Bullet();

    //METHODS
    virtual std::string toString() const override;
    bool improve();

    //SETTERS
    void setPrice(int price);
    
    //GETTERS
    int getDamage() const;

    void move(const float x, const float y) override;
    int getType() const;
    
    int getState() const;
    int getPrice() const;
    
};

#endif // BULLET_H_INCLUDED
