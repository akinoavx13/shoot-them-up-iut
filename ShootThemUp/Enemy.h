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
    float _xEntree;
    float _xSortie;
    float _yEntree;
    float _ySortie;

public:

    //CONSTRUCTOR
    Enemy();
    Enemy(const float x, const float y, const int health, const int type, const int width, const int height);
    Enemy(const float x, const float y, const int health, const int type, const int width, const int height, const float firerate);
    static Enemy* Tiny(const float x, const float y);
    static Enemy* Submarine(const float x, const float y);
    static Enemy* Mighty(const float x, const float y);

    //DESTRUCTOR
    virtual ~Enemy();

    //METHODS
    virtual std::string toString() const override;
    void shoot() override;
    void shoot(const float x, const float y, const float speedX, const float speedY);
    void move(const float x, const float y) override;


    //GETTER
    int getType() const;
    
    float getXEntree() const;
    float getXSortie() const;
    float getYEntree() const;
    float getYSortie() const;
    
    void setXEntree(float x);
    void setXSortie(float x);
    void setYEntree(float y);
    void setYSortie(float y);

};

#endif // ENEMY_H_INCLUDED
