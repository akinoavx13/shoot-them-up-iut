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
 * CONSTRUCTOR
 */
GameModel::GameModel():_numberTour(1), _bossMoveIncrement(0), _enemyMoveIncrement(0), _difficulty(3){
#ifdef __linux__
    _level = nullptr;
#else
    _level = 0;
#endif
}

/*
 * DESTRUCTOR
 */
GameModel::~GameModel(){
    delete _level;
}

/*
 * METHODS
 */
//the main function of the game. It's update all variables in the game
void GameModel::updateCore(){

    //if we are in the menu state
    if(_menu->getMenu())
    {
#ifdef __linux__
        if(_level == nullptr){
#else
        if(_level == 0){
#endif
            _level = new Level();
        }

        _numberTour = 0;
        _bossMoveIncrement = 0;
        _enemyMoveIncrement = 0;

    }

    //if we are in the game
    else if(_menu->getGame())
    {
        _numberTour++;

        //screen when it's write "get ready"
        if(_menu->getReady()){

            //in function of the theme, we set the size of images
            if(_menu->getTheme() == 0){
                _level->getAlly()->changeSize(ALLY_PICTURE_WIDTH/3, ALLY_PICTURE_HEIGHT);
                for(auto e : _level->getEnemies())
                {
                    if(e->getType()==1)
                    {
                        e->changeSize(TINY_PICTURE_WIDTH/3, TINY_PICTURE_HEIGHT);
                    }
                    else if(e->getType()==2)
                    {
                        e->changeSize(SUBMARINE_PICTURE_WIDTH/2, SUBMARINE_PICTURE_HEIGHT);
                    }
                    else if(e->getType()==3)
                    {
                        e->changeSize(MIGHTY_PICTURE_WIDTH/3, MIGHTY_PICTURE_HEIGHT);
                    }
                }
            }

            //in function of the theme, we set the size of images
            else if (_menu->getTheme()==1){
                _level->getAlly()->changeSize(SECOND_ALLY_WIDTH, SECOND_ALLY_HEIGHT/3);
                for(auto e : _level->getEnemies())
                {
                    if(e->getType()==1)
                    {
                        e->changeSize(SECOND_TINY_WIDTH, SECOND_TINY_HEIGHT);
                    }
                    else if(e->getType()==2)
                    {
                        e->changeSize(SECOND_SUBMARINE_WIDTH, SECOND_SUBMARINE_HEIGHT);
                    }
                    else if(e->getType()==3)
                    {
                        e->changeSize(SECOND_MIGHTY_WIDTH, SECOND_MIGHTY_HEIGHT);
                    }
                }
            }
        }

        //if we are playing
        else if(_menu->getLevel())
        {
            //move bullets
            _level->moveBullets();

            //check all collisions
            _level->checkCollisions();

            //check if ally is dead (health points <= 0)
            if(_level->getAlly()->isDead() )
            {
                //and player have life, we set his health points to maximum
                if(!_level->getAlly()->isOver())
                {
                    _level->getAlly()->setHealth(ALLY_LIFE);
                    _level->getAlly()->setNumberOfLife(getLevel()->getAlly()->getNumberOfLife() - 1);
                }

                //else he's don't have any life, so it's finish. He can save his score
                else{
                    _menu->setLevel(false);
                    _menu->setShop(false);
                    _menu->setSaveScore(true);
                }
            }

            //if they are no enemies on the field
            if(_level->getEnemiesNumber() == 0)
            {
                //and also no boss
#ifdef __linux__
                if(_level->getBoss() == nullptr)
#else
                if(_level->getBoss() == 0)
#endif
                {
                    //update level number
                    _level->setLevelNumber(_level->getLevelNumber() + 1);

                    //add to enemies
                    _level->setNbEnemies(_level->getNbEnemies() + _difficulty);
                    _level->addEnemies();

                    //increase the life of enemies for the next level and increase the damage.
                    //we put another bullet type for enemies in function of the level number
                    for (auto enemy : _level->getEnemies())
                    {
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

                    //set the position of the player in the middle
                    _level->getAlly()->move(MODEL_WIDTH / 2 - _level->getAlly()->getWidth() / 2, MODEL_HEIGHT - _level->getAlly()->getHeight() - 25);

                    //get all bonus shoot
                    _level->getAlly()->resetBonus();

                    //and go to the shop to buy some bonus !
                    _menu->setShop(true);
                    _menu->setLevel(false);
                }

                //if the boss is present
#ifdef __linux__
                else if(_level->getBoss() != nullptr &&  !_level->getBoss()->isDead())
#else
                else if(_level->getBoss() != 0 &&  !_level->getBoss()->isDead())
#endif
                {
                    //boss shoot
                    if(shoot.GetElapsedTime() >= _level->getBoss()->getFireRate())
                    {
                        //allow to shoot 20 bullet in circle
                        for (int i = 0; i < 360; i += 18) {
                            int max = std::max(_level->getBoss()->getHeight(), _level->getBoss()->getWidth());

                            float xb = max * cos((float)i * (3.14/180)) + _level->getBoss()->getX() + _level->getBoss()->getWidth() / 2;
                            float yb = max * sin((float)i * (3.14/180)) + _level->getBoss()->getY() + _level->getBoss()->getHeight() / 2;

                            _level->getBoss()->shoot(xb, yb, 13*cos((float)i * (3.14/180)), 13*sin((float)i * (3.14/180)));

                        }

                        shoot.Reset();
                    }

                    //and move the boss in circle too
                    _bossMoveIncrement++;
                    float xBoss = 200 * cos((float)_bossMoveIncrement * (3.14/180)) + MODEL_WIDTH / 2 - BOSS_PICTURE_WIDTH / 6;
                    float yBoss = 200 * sin((float)_bossMoveIncrement * (3.14/180)) + MODEL_HEIGHT / 2 - BOSS_PICTURE_HEIGHT / 2 - 100;
                    _level->getBoss()->move(xBoss, yBoss);
                }
            }

            else
            {
                //we add the boss when the level have just 1 enemy
                if(_level->getEnemiesNumber() == 1)
                {
                    _level->addBoss();

                    //increase his life
                    _level->getBoss()->setHealth(getLevel()->getBoss()->getHealth() + (_level->getLevelNumber() - 1) * 50 );

                    //inscrease his damage
                    _level->getBoss()->setDamage(_level->getBoss()->getDamage() + _level->getLevelNumber() * 10);

                    //set the bullet type
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

                //enemies shoot
                if(shoot.GetElapsedTime() >= ENEMY_FIRERATE)
                {
                    _level->EnemiesShoot();
                    shoot.Reset();
                }
            }

            //enemies move
            _level->moveEnemies(_enemyMoveIncrement);
            _enemyMoveIncrement += 0.1;
        }

        else if (_menu->getShop())
        {
            _level->deleteAllBullets();
        }
        else if(_menu->getReady()){

        }
        else if(_menu->getSaveScore()){

        }
        else{
#ifdef __linux__
            _level=nullptr;
#else
            _level=0;
#endif
            _menu->setMenu(true);
            _menu->setGame(false);
        }
    }

    //quit the game
    else if(_menu->getEnding())
    {
        _menu->setIntro(false);
        _menu->setGame(false);
        _menu->setLevel(false);
        _menu->setShop(false);
        _menu->setMenu(true);
        _menu->setScore(false);
        _menu->setSaveScore(false);
    }
}

//clear the screen
void GameModel::clearScreen() const{
    #ifdef __linux__
        system("clear");
    #else
    for (int i = 0; i < 10; i++) {
        cout << endl;
    }
    #endif

}

/*
 * GETTERS
 */
Level* GameModel::getLevel() const{
    return _level;
}

int GameModel::getNumberTour() const{
    return _numberTour;
}

int GameModel::getDifficulty() const{
    return _difficulty;
}

/*
 * SETTERS
 */
void GameModel::setMenu(Menu* menu){
    _menu = menu;
}

void GameModel::setDifficulty(int difficulty){
    _difficulty = difficulty;
}
