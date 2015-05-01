//
//  GraphicElement.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "GraphicElement.h"

using namespace std;

/*
 * default contructor
 */
GraphicElement::GraphicElement():_x(DEFAULT_GRAPHIC_ELEMENT_X), _y(DEFAULT_GRAPHIC_ELEMENT_Y), _speedX(DEFAULT_GRAPHIC_ELEMENT_SPEED_X), _speedY(DEFAULT_GRAPHIC_ELEMENT_SPEED_Y), _width(DEFAULT_GRAPHIC_ELEMENT_WIDTH), _height(DEFAULT_GRAPHIC_ELEMENT_HEIGHT){}

/*
 * constructor to created a graphic element with x and y value
 * params : position x of graphic element, position y of graphic element
 */
GraphicElement::GraphicElement(const float x, const float y, const int width, const int height, const int speedX, const int speedY):_x(x), _y(y), _speedX(speedX), _speedY(speedY), _width(width), _height(height){}

/*
 * destructor
 * info : abstract, virtual
 */
GraphicElement::~GraphicElement(){}

//----------METHODS----------
/*
 * move graphic element
 * params : new x and new y position of graphic element
 */
void GraphicElement::move(const float x, const float y){
    if (x >= 0 && x+_width < MODEL_WIDTH) {
        _x = x;
    }else{
        cout << "X n'est pas compris entre 0 et " << MODEL_WIDTH << ". X vaut : " << x << endl;
    }

    if (y >= 0 && y+_height < MODEL_HEIGHT) {
        _y = y;
    }else{
        cout << "Y n'est pas compris entre 0 et " << MODEL_HEIGHT << ". Y vaut : " << y << endl;
    }
}

/*
 * info : constant, virtual
 * returns : string, x and y position
 */
string GraphicElement::toString() const{
    string str;

    str += "\tPosition X : " + to_string(_x) + "\n";
    str += "\tPosition Y : " + to_string(_y) + "\n";
    str += "\tTaille :\n";
    str += "\t\tLargeur : " + to_string(_width) + "\n";
    str += "\t\tHauteur : " + to_string(_height) + "\n";

    return str;
}

//----------GETTERS----------
/*
 * returns : x position of graphic element
 */
float GraphicElement::getX() const{
    return _x;
}

/*
 * returns : y position of graphic element
 */
float GraphicElement::getY() const{
    return _y;
}

/*
 * returns : x speed of graphic element
 */
float GraphicElement::getSpeedX() const{
    return _speedX;
}

/*
 * returns : y speed of graphic element
 */
float GraphicElement::getSpeedY() const{
    return _speedY;
}

/*
 * returns : width of graphic element
 */
int GraphicElement::getWidth() const{
    return _width;
}

/*
 * returns : height of graphic element
 */
int GraphicElement::getHeight() const{
    return _height;
}
