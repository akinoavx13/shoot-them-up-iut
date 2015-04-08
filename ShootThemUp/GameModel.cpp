//
//  GameModel.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "GameModel.h"

using namespace std;

/*
 * default constructor
 * params : Model width, Model height, number tour
 */
GameModel::GameModel():_WIDTH(MODEL_WIDTH), _HEIGHT(MODEL_HEIGHT), _numberTour(0){
    _level = new Level();
}

/*
 * destructor
 */
GameModel::~GameModel(){
    delete _level;
    
}

//----------METHODS----------
/*
 * principal methods who is always called.
 * used to change value of variables
 */
void GameModel::updateCore(){
    _numberTour++;
    
    clearScreen();
    
    /*
    if(_level->getEnemiesNumber() > 0){
        //enemies shoot every 2 turns
        if(_numberTour % 2 == 0){
            getLevel()->EnemiesShoot();
        }
        
        //enemies move every 4 turns
        if(_numberTour % 4 == 0){
            getLevel()->moveEnemies();
        }
    }
    
    if(_level->getBoss() != nullptr &&  !_level->getBoss()->isDead()){
        //boss shoot every 4 turns
        if(_numberTour % 2 == 0){
            _level->getBoss()->shoot();
        }

    }
    */
    getLevel()->checkCollisions();
    /*
    //check if ally is dead
    if(getLevel()->getAlly()->isDead()){
        //and game is not finished
        if(!getLevel()->getAlly()->isOver()){
            getLevel()->getAlly()->setHealth(DEFAULT_SHIP_LIFE);
            getLevel()->getAlly()->setNumberOfLife(getLevel()->getAlly()->getNumberOfLife() - 1);
        }
    }
     */
}

/*
 * clear the screen
 * info : constant
 */
void GameModel::clearScreen() const{
    for (int i = 0; i < 10; i++) {
        cout << endl;
    }
}

//----------GETTERS----------
/*
 * returns : level
 * info : constant
 */
Level* GameModel::getLevel() const{
    return _level;
}

/*
 * returns : the number of turns
 * info : constant
 */
int GameModel::getNumberTour() const{
    return _numberTour;
}

void GameModel::setMenu(Menu* menu){
    _menu = menu;
}