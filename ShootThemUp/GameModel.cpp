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
GameModel::GameModel():_WIDTH(MODEL_WIDTH), _HEIGHT(MODEL_HEIGHT), _numberTour(1), _level(nullptr) {}

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
    if(_menu->getMenu()){
            _level = new Level();
            _numberTour=0;

    }
    if(_menu->getGame()){

        _numberTour++;
        clearScreen();

        if(_menu->getLevel()){
            getLevel()->moveBullets();
            getLevel()->checkCollisions();

            //check if ally is dead
            if(getLevel()->getAlly()->isDead()){
                //and game is not finished
                if(!getLevel()->getAlly()->isOver()){
                    getLevel()->getAlly()->setHealth(DEFAULT_SHIP_LIFE);
                    getLevel()->getAlly()->setNumberOfLife(getLevel()->getAlly()->getNumberOfLife() - 1);
                }
            }
            if(getLevel()->getAlly()->isOver()){
                _menu->setIntro(false);
                _menu->setGame(false);
                _menu->setLevel(false);
                _menu->setShop(false);
                _menu->setMenu(false);
                _menu->setScore(false);
                _menu->setEnding(false);
                _menu->setSaveScore(true); //go to save score because ally is dead
            }

            if(getLevel()->getEnemiesNumber() == 1){
                getLevel()->addBoss();
                getLevel()->getBoss()->setHealth(getLevel()->getBoss()->getHealth() + getLevel()->getLevelNumber() * 30);
            }

            if(getLevel()->getEnemiesNumber() <= 0){
                if(getLevel()->getBoss() == nullptr){
                    _menu->setIntro(false);
                    _menu->setGame(false);
                    _menu->setLevel(false);
                    _menu->setShop(true); //go to shop because level is finish
                    _menu->setMenu(false);
                    _menu->setScore(false);
                    _menu->setEnding(false);
                }
                if(_level->getBoss() != nullptr &&  !_level->getBoss()->isDead()){
                    //boss shoot every 2 turns
                    if(_numberTour % 2 == 0){
                        _level->getBoss()->shoot();
                    }

                    //boss shoot every 4 turns
                    if(_numberTour % 3 == 0){
                        int x;
                        int y = 100;
                        x = rand() % MODEL_WIDTH + 1;
                        srand((unsigned int)time(NULL));
                        _level->getBoss()->move(x, y);
                    }
                }
            }
            else{
                //enemies shoot every 2 turns
                if(_numberTour % 2 == 0){
                    getLevel()->EnemiesShoot();
                }

                //enemies move every 4 turns
                if(_numberTour % 4 == 0){
                    getLevel()->moveEnemies();
                }
            }

        }

        if (_menu->getShop()) {
            _level->setLevelNumber(_level->getLevelNumber() + 1);
            _level->setNbEnemies(_level->getNbEnemies() + 2);
            _level->addEnemies();
            for (auto enemy : getLevel()->getEnemies()) {
                enemy->setHealth(enemy->getHealth() + getLevel()->getLevelNumber() * 10);
                enemy->setDamage(enemy->getDamage() + getLevel()->getLevelNumber() * 7);
            }
        }
    }

    if(_menu->getSaveScore()){
        delete _level;
    }

    if(_menu->getEnding()){
        _menu->setIntro(false);
        _menu->setGame(false);
        _menu->setLevel(false);
        _menu->setShop(false);
        _menu->setMenu(true);
        _menu->setScore(false);
        _menu->setSaveScore(false);
    } //all is false and we quit the game
}

/*
 * clear the screen
 * info : constant
 */
void GameModel::clearScreen() const{
    #ifdef __linux
        system("clear");
    #else
    for (int i = 0; i < 10; i++) {
        cout << endl;
    }
    #endif

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
