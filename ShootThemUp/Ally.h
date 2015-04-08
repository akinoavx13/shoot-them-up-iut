//
//  Ally.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__Ally__
#define __ShootThemUp__Ally__

#include <stdio.h>
#include <string>
#include <iostream>

#include "Ship.h"

class Ally : public Ship{
private:
    
    int _numbersOfLife;
    int _score;
    
public:

    //CONSTRUCTOR
    Ally();
    Ally(const float x, const float y, const int health);
    
    //DESTRUCTOR
    virtual ~Ally();

    //METHODS
    bool isOver() const;
    std::string toString() const override;
    
    //GETTERS
    int getNumberOfLife() const;

    //SETTERS
    void setHealth(int health);
    void setNumberOfLife(int numberOfLive);
    
    void setPoint(int expPoint);

};

#endif /* defined(__ShootThemUp__Ally__) */
