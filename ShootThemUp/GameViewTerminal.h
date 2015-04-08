//
//  GameView.h
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__GameView__
#define __ShootThemUp__GameView__

#include <stdio.h>
#include <iostream>

#include "GameModel.h"
#include "GraphicElement.h"
#include "const.h"
#include "Menu.h"

class GameViewTerminal {
    
private:
    
    GameModel* _gameModel;
    Menu* _menu;
    
public:
    
    //CONSTRUCTOR
    GameViewTerminal();
    
    //DESTRUCTOR
    ~GameViewTerminal();
    
    //METHODS
    void draw() const;
    
    //SETTERS
    void setModel(GameModel* gameModel);
    void setModelMenu();
    
    bool treatEvent();
    
};

#endif /* defined(__ShootThemUp__GameView__) */
