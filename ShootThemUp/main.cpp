//
//  main.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 25/02/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "GameModel.h"
#include "GameViewTerminal.h"

using namespace std;

int main(){

    GameModel* gameModel = new GameModel();
    GameViewTerminal* gameViewTermial = new GameViewTerminal();

    gameViewTermial->setModel(gameModel);
    gameViewTermial->setModelMenu();
    
    //boucle principale du jeu
    while (!gameViewTermial->treatEvent()) {
        gameViewTermial->draw();
        gameModel->updateCore();
    }
    
    delete gameModel;
    delete gameViewTermial;

    return EXIT_SUCCESS;
}
