//
//  GameViewSFML.h
//  ShootThemUp
//
//  Created by Nicolas on 01/05/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include "SFML/Graphics.hpp"

class Picture{
private:
    sf::Sprite * _sprite;
    int _x;
    int _y;
    int _width;
    int _height;


public:
    Picture(sf::Image * image);
    Picture(sf::Image * image, int x, int y);
    Picture(sf::Image * image, int x, int y, int width, int height);
    Picture(sf::Image * image, int x, int y, int width, int height, int x1, int y1, int x2, int y2);
    ~Picture();

    sf::Sprite getSprite() const;
};


#endif // PICTURE_H_INCLUDED
