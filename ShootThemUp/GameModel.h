//
//  GameModel.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__GameModel__
#define __ShootThemUp__GameModel__

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "const.h"
#include "Level.h"
#include "Menu.h"

class GameModel{

private:

    const int _WIDTH;
    const int _HEIGHT;

    Menu* _menu;
    Level* _level;
    int _numberTour;
    
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
