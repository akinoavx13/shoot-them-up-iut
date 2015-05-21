//
//  GraphicElement.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "GraphicElement.h"

using namespace std;
using namespace sf;

/*
 * CONSTRUCTOR
 */
GraphicElement::GraphicElement():_x(GRAPHIC_ELEMENT_X), _y(GRAPHIC_ELEMENT_Y), _speedX(GRAPHIC_ELEMENT_SPEED_X), _speedY(GRAPHIC_ELEMENT_SPEED_Y), _width(GRAPHIC_ELEMENT_WIDTH), _height(GRAPHIC_ELEMENT_HEIGHT){}

GraphicElement::GraphicElement(const float x, const float y, const int width, const int height, const float speedX, const float speedY):_x(x), _y(y), _speedX(speedX), _speedY(speedY), _width(width), _height(height){}

/*
 * DESTRUCTOR
 */
GraphicElement::~GraphicElement(){}

/*
 * METHODS
 */
//move a graphics element to x and y position
void GraphicElement::move(const float x, const float y){
    if (x >= 0 && x+_width < MODEL_WIDTH) {
        _x = x;
    }
    if (y >= 0 && y+_height < MODEL_HEIGHT) {
        _y = y;
    }
}

//return true if they is a collision beteween 2 graphics elements
bool GraphicElement::collisions(GraphicElement* graphicElement)const{
    int aLeft = _x;
    int aTop = _y;
    int aRight = _x+_width;
    int aBottom = _y+_height;

    int bLeft = graphicElement->getX();
    int bTop = graphicElement->getY();
    int bRight = graphicElement->getX() + graphicElement->getWidth();
    int bBottom = graphicElement->getY() + graphicElement->getHeight();

    if(
        (aLeft >= bLeft && aLeft <= bRight && aTop >= bTop && aTop <= bBottom) ||
        (aRight >= bLeft && aRight <= bRight && aTop >= bTop && aTop <= bBottom) ||
        (aLeft >= bLeft && aLeft <= bRight && aBottom >= bTop && aBottom <= bBottom) ||
        (aRight >= bLeft && aRight <= bRight && aBottom >= bTop && aBottom <= bBottom) ||
        (aRight >= bRight && aLeft <= bLeft && ((bTop <= aTop && bBottom >= aTop) || (bTop <=aBottom && bBottom>=aBottom))) ||
        (aTop <= bTop && aBottom >=bTop && ( (aRight>=bRight && aLeft<= bRight) || (aLeft<=bLeft && aRight>= bLeft) ) )
    ){
        return true;
    }
    return false;

}

//write some informations of the graphics element
string GraphicElement::toString() const{
    string str;

    #ifdef __linux__
    str += "\tPosition X : " + to_string(_x) + "\n";
    str += "\tPosition Y : " + to_string(_y) + "\n";
    str += "\tTaille :\n";
    str += "\t\tLargeur : " + to_string(_width) + "\n";
    str += "\t\tHauteur : " + to_string(_height) + "\n";
    #endif
    return str;
}

//change the size of a graphic element
void GraphicElement::changeSize(int width, int height){
    _height=height;
    _width=width;
}

/*
 * GETTERS
 */
float GraphicElement::getX() const{
    return _x;
}

float GraphicElement::getY() const{
    return _y;
}

float GraphicElement::getSpeedX() const{
    return _speedX;
}

float GraphicElement::getSpeedY() const{
    return _speedY;
}

int GraphicElement::getWidth() const{
    return _width;
}

int GraphicElement::getHeight() const{
    return _height;
}