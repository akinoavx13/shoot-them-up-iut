//
//  GameModel.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__GameModel__
#define __ShootThemUp__GameModel__

#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "const.h"
#include "Level.h"
#include "Menu.h"

class GameModel{

private:

    Menu* _menu;
    Level* _level;
    int _numberTour;
    sf::Clock shoot;
    int _bossMoveIncrement;

public:

    //CONSTRUCTOR
    GameModel();

    //DESTRUCTOR
    ~GameModel();

    //METHODS
    void updateCore();
    void clearScreen() const;

    //GETTERS
    Level* getLevel() const;
    int getNumberTour() const;

    void setMenu(Menu* menu);

};

#endif /* defined(__ShootThemUp__GameModel__) */
