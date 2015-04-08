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

public:
    
    //CONSTRUCTOR
    Bullet();
    Bullet(const float x, const float y, const int damage);
    
    //DESTRUCTOR
    virtual ~Bullet();
    
    //METHODS
    virtual std::string toString() const override;
    
    //GETTERS
    int getDamage() const;
        
};

#endif // BULLET_H_INCLUDED
