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
#include "GameViewSFML.h"

using namespace std;

int main(){

    GameModel* gameModel = new GameModel();
    //GameViewTerminal* gameView = new GameViewTerminal();
    GameViewSFML* gameView = new GameViewSFML();

    gameView->setModel(gameModel);
    gameView->setModelMenu();

    //boucle principale du jeu
    while (gameView->treatEvent()) {
        gameModel->updateCore();
        gameView->draw();

    }

    delete gameModel;
    delete gameView;

    return EXIT_SUCCESS;
}
