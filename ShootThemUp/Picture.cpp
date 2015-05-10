//
//  GameViewSFML.h
//  ShootThemUp
//
//  Created by Nicolas on 01/05/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#include "Picture.h"
#include <iostream>

using namespace sf;

Picture::Picture(sf::Image * image){
    _x=0;
    _y=0;
    _width=50;
    _height=50;
    _sprite->SetImage(*image);
    _sprite->SetX(_x);
    _sprite->SetY(_y);
    _sprite->Resize(_width, _height);
}

Picture::Picture(sf::Image * image, float x, float y){
    _x=x;
    _y=y;
    _width=50;
    _height=50;
    _sprite->SetImage(*image);
    _sprite->SetX(_x);
    _sprite->SetY(_y);
    _sprite->Resize(_width, _height);
}

Picture::Picture(sf::Image * image, float x, float y, int width, int height){
    _x=x;
    _y=y;
    _width=width;
    _height=height;
    _sprite = new Sprite();
    _sprite->SetImage(*image);
    _sprite->SetX(_x);
    _sprite->SetY(_y);
    _sprite->Resize(_width, _height);
}

Picture::Picture(sf::Image * image, float x, float y, int width, int height, int x1, int y1, int x2, int y2){
    _x=x;
    _y=y;
    _width=width;
    _height=height;
    _sprite = new Sprite();
    _sprite->SetImage(*image);
    _sprite->SetX(_x);
    _sprite->SetY(_y);
    _sprite->Resize(_width, _height);

    IntRect subRect;
    subRect.Left = x1;
    subRect.Top = y1;
    subRect.Right = x2;
    subRect.Bottom = y2;


    _sprite->SetSubRect(subRect);
}


Picture::~Picture(){
    delete _sprite;
}

Sprite Picture::getSprite() const{
    return *_sprite;
}


