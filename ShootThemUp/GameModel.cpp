//
//  GameModel.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "GameModel.h"
#include <math.h>
#include <algorithm>

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
            cout << "cour" << endl;
            _level = new Level();
        }
#endif
        _numberTour=0;
         _bossMoveIncrement = 0;
        
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
                     _menu->setShop(false);
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
                    _level->deleteAllEnemy();
                    _level->deleteAllBullets();
                    
                    
                    _level->setLevelNumber(_level->getLevelNumber() + 1);
                    _level->setNbEnemies(_level->getNbEnemies() + 2);
                    _level->addEnemies();
                    for (auto enemy : _level->getEnemies())
                    {
                        //ici on peut ajouter de la vie au ennemis
                        enemy->setHealth(enemy->getHealth() + (_level->getLevelNumber() - 1) * 10);
                        enemy->setDamage(enemy->getDamage() + _level->getLevelNumber() * 2);
                        
                        if(_level->getLevelNumber() >= 2){
                            enemy->setBulletType(1);
                        }
                        if(_level->getLevelNumber() >= 3){
                            enemy->setBulletType(2);
                        }
                        if(_level->getLevelNumber() >= 4){
                            enemy->setBulletType(4);
                        }
                        if(_level->getLevelNumber() >= 5){
                            enemy->setBulletType(3);
                        }
                    }
                    
                    _level->getAlly()->move(SCREEN_WIDTH/2, SCREEN_HEIGHT-ALLY_PICTURE_HEIGHT-10);
                    
                    _menu->setShop(true); //go to shop because level is finish
                    _menu->setLevel(false);
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
                        
                        for (int i = 0; i < 360; i+=18) {
                            int max = std::max(_level->getBoss()->getHeight(), _level->getBoss()->getWidth());
                            
                            float xb = max * cos((float)i * (3.14/180)) + _level->getBoss()->getX() + _level->getBoss()->getWidth() / 2;
                            float yb = max * sin((float)i * (3.14/180)) + _level->getBoss()->getY() + _level->getBoss()->getHeight() / 2;
                            
                            _level->getBoss()->shoot(xb, yb, 10*cos((float)i * (3.14/180)), 10*sin((float)i * (3.14/180)));
                            
                        }
                        
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
                    _level->getBoss()->setDamage(_level->getBoss()->getDamage() + _level->getLevelNumber() * 2);
                    if(_level->getLevelNumber() >= 2){
                        _level->getBoss()->setBulletType(1);
                    }
                    if(_level->getLevelNumber() >= 3){
                        _level->getBoss()->setBulletType(2);
                    }
                    if(_level->getLevelNumber() >= 4){
                        _level->getBoss()->setBulletType(4);
                    }
                    if(_level->getLevelNumber() >= 5){
                        _level->getBoss()->setBulletType(3);
                    }

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

        }
    }
    
    else if(_menu->getSaveScore()){
#ifdef __linux__
        _level=nullptr;
#else
        _level=0;
#endif
        
        _menu->setMenu(true);
        _menu->setSaveScore(false);
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
