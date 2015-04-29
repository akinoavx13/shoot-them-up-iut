//
//  GameViewSFML.h
//  ShootThemUp
//
//  Created by Nicolas on 28/04/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#ifndef GAMEVIEWSFML_H_INCLUDED
#define GAMEVIEWSFML_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "GameModel.h"
#include "Menu.h"
#include "GraphicLibrary.h"

class GameViewSFML{
private:
    sf::RenderWindow * _window;

    GameModel* _gameModel;
    Menu* _menu;

    GraphicLibrary* _graphicLibrary;

public:
    //CONSTRUCTOR
    GameViewSFML();

    //DESTRUCTOR
    ~GameViewSFML();

    //METHODS
    void draw() const;

    //SETTERS
    void setModel(GameModel* gameModel);
    void setModelMenu();

    bool treatEvent();

};

#endif // GAMEVIEWSFML_H_INCLUDED
