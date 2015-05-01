//
//  Enemy.h
//  ShootThemUp
//
//  Created by Nicolas Valaise on 18/03/2015.
//  Copyright (c) 2015 Nicolas Valaise. All rights reserved.
//

#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include <string>
#include <iostream>

#include "Ship.h"

class Enemy : public Ship{

private:
    int _type;

public:

    //CONSTRUCTOR
    Enemy();
    Enemy(const float x, const float y, const int health, const int type, const int width, const int height);
    static Enemy* Tiny(const float x, const float y);
    static Enemy* Submarine(const float x, const float y);
    static Enemy* Mighty(const float x, const float y);

    //DESTRUCTOR
    virtual ~Enemy();

    //METHODS
    virtual std::string toString() const override;
    void shoot() override;

    //GETTER
    int getType() const;
};

#endif // ENEMY_H_INCLUDED
