//
//  GameModel.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "GameModel.h"
#include <math.h>

using namespace std;

/*
 * default constructor
 * params : Model width, Model height, number tour
 */
GameModel::GameModel():_numberTour(1), _bossMoveIncrement(0){
    #ifdef __linux__
        _level = nullptr;
    #else
        _level = 0;
    #endif

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
    if(_menu->getMenu())
    {
#ifdef __linux__
        if(_level==nullptr){
            _level = new Level();
        }
#else
        if(_level == 0){
            _level = new Level();
        }
#endif
        _numberTour=0;
        
    }
    else if(_menu->getGame())
    {
        _numberTour++;
        //clearScreen();
        
        if(_menu->getLevel())
        {
            _level->moveBullets();
            _level->checkCollisions();
            
            //check if ally is dead
            if(_level->getAlly()->isDead() )
            {
                //and game is not finished
                if(!_level->getAlly()->isOver())
                {
                    _level->getAlly()->setHealth(ALLY_LIFE);
                    _level->getAlly()->setNumberOfLife(getLevel()->getAlly()->getNumberOfLife() - 1);
                }
                else{
                    _menu->setGame(false);
                    _menu->setLevel(false);
                    _menu->setSaveScore(true); //go to save score because ally is dead
                }
            }
            if(_level->getEnemiesNumber() == 0)
            {
                
                #ifdef __linux__
                if(_level->getBoss() == nullptr)
                #else
                if(_level->getBoss() == 0)
                #endif
                {
                    _menu->setShop(true); //go to shop because level is finish
                    _menu->setLevel(false);
                    
                    _level->setLevelNumber(_level->getLevelNumber() + 1);
                    _level->setNbEnemies(_level->getNbEnemies() + 2);
                    _level->addEnemies();
                    for (auto enemy : _level->getEnemies())
                    {
                        //ici on peut ajouter de la vie au ennemis
                        enemy->setHealth(enemy->getHealth() + (_level->getLevelNumber() - 1) * 10);
                        enemy->setDamage(enemy->getDamage() + getLevel()->getLevelNumber());
                    }
                }
                    
                #ifdef __linux__
                else if(_level->getBoss() != nullptr &&  !_level->getBoss()->isDead())
                #else
                else if(_level->getBoss() != 0 &&  !_level->getBoss()->isDead())
                #endif
                {
                    //boss shoot every 2 turns
                    if(shoot.GetElapsedTime() >= _level->getBoss()->getFireRate())
                    {
                        _level->getBoss()->shoot();
                        shoot.Reset();
                    }
                            
                    _bossMoveIncrement++;
                    float xBoss = 50 * cos((float)_bossMoveIncrement * (3.14/180)) + SCREEN_WIDTH / 2 - BOSS_PICTURE_WIDTH / 6;
                    float yBoss = 50 * sin((float)_bossMoveIncrement * (3.14/180)) + SCREEN_HEIGHT / 2 - BOSS_PICTURE_HEIGHT / 2 - 100;
                    _level->getBoss()->move(xBoss, yBoss);
                }
            }

            else
            {
                if(_level->getEnemiesNumber() == 1)
                {
                    _level->addBoss();
                    //ici on peut ajouter de la vie au boss
                    _level->getBoss()->setHealth(getLevel()->getBoss()->getHealth() + (_level->getLevelNumber() - 1) * 30 );
                }
                //enemies shoot every 2 turns
                if(shoot.GetElapsedTime() >= ENEMY_FIRERATE)
                {
                    _level->EnemiesShoot();
                    shoot.Reset();
                }
            }
            _level->moveEnemies();
            
        }
        
        else if (_menu->getShop())
        {
            _level->setLevelNumber(_level->getLevelNumber() + 1);
            _level->setNbEnemies(_level->getNbEnemies() + 2);
            _level->addEnemies();
            for (auto enemy : _level->getEnemies())
            {
                //ici on peut ajouter de la vie au ennemis
                enemy->setHealth(enemy->getHealth() + _level->getLevelNumber());
                enemy->setDamage(enemy->getDamage() + _level->getLevelNumber());
            }
        }
    }
    
    else if(_menu->getSaveScore()){
        
    }
    
    else if(_menu->getEnding())
    {
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
    #ifdef __linux__
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
