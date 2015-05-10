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

public:
    //CONSTRUCTOR
    Bullet();
    Bullet(const float x, const float y, const int damage, const int width, const int height, const int speedX, const int speedY, const int type);
    static Bullet* FireBall(const float x, const float y);
    static Bullet* TinyLaser(const float x, const float y);
    static Bullet* Laser(const float x, const float y);

    //DESTRUCTOR
    virtual ~Bullet();

    //METHODS
    virtual std::string toString() const override;

    //GETTERS
    int getDamage() const;

    void move(const float x, const float y) override;
    int getType() const;

};

#endif // BULLET_H_INCLUDED
