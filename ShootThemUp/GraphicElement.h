//
//  GraphicElement.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__GraphicElement__
#define __ShootThemUp__GraphicElement__

#include <stdio.h>
#include <string>
#include <iostream>

#include "const.h"

class GraphicElement{

protected:

    float _x;
    float _y;

    float _speedX;
    float _speedY;

    int _width;
    int _height;

public:

    //CONSTRUCTOR
    GraphicElement();
    GraphicElement(const float x, const float y, const int width, const int height, const int speedX, const int speedY);

    //DESTRUCTOR
    virtual ~GraphicElement() = 0;

    //METHODS
    virtual void move(const float x, const float y);
    virtual std::string toString() const;

    //GETTERS
    float getX() const;
    float getY() const;
    float getSpeedX() const;
    float getSpeedY() const;
    int getWidth() const;
    int getHeight() const;

};

#endif /* defined(__ShootThemUp__GraphicElement__) */
