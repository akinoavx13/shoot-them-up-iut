//
//  Level.h
//  ShootThemUp
//
//  Created by Nicolas Valaise on 18/03/2015.
//  Copyright (c) 2015 Nicolas Valaise. All rights reserved.
//

#ifndef __LEVEL_H_INCLUDED__
#define __LEVEL_H_INCLUDED__

#include <vector>
#include <time.h>

#include "const.h"
#include "Enemy.h"
#include "Ally.h"
#include "Bullet.h"
#include "Boss.h"

class Level{

private:

    int _levelNumber;
    int _nbEnemies;

    std::vector<Enemy *> _tabEnemies;
    std::vector<Bullet*> _tabBullets;

    Boss* _boss;
    Ally* _ally;

public:

    //CONSTRUCTOR
    Level();

    //DESTRUCTOR
    virtual ~Level();

    //METHODS
    bool isFinish() const;
    std::string toString() const;
    void checkCollisions();
    void addBullet(Bullet* bullet);
    void moveEnemies(float i);
    void EnemiesShoot() const;
    void addBoss();
    void addEnemies();
    void deleteAllEnemy();
    void deleteAllBullets();

    void moveBullets();

    //GETTERS
    Ally* getAlly() const;
    Boss* getBoss() const;
    std::vector<Enemy*> getEnemies() const;
    std::vector<Bullet*> getBullets() const;
    int getEnemiesNumber() const;
    int getNbEnemies()const;
    int getLevelNumber() const;
    int getNumberOfBullets() const;
    int getNumberOfEnemies() const;

    //SETTERS
    void setNbEnemies(int nbEnemies);
    void setLevelNumber(int levelNumber);

};

#endif // LEVEL_H_INCLUDED
