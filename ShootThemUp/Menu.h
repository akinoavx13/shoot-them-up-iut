//
//  Menu.h
//  ShootThemUp
//
//  Created by Nicolas on 30/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__Menu__
#define __ShootThemUp__Menu__

#include <stdio.h>
#include <iostream>
#include <string>

#include "Player.h"

class Menu {
private:
    bool _intro;
    bool _game;
    bool _level;
    bool _shop;
    bool _menu;
    bool _score;
    bool _ending;
    
public:
    Menu();
    ~Menu();
    
    bool getIntro() const;
    void setIntro(bool intro);

    bool getGame() const;
    void setGame(bool shop);
    
    bool getLevel() const;
    void setLevel(bool level);
    
    bool getShop() const;
    void setShop(bool shop);
    
    bool getMenu() const;
    void setMenu(bool menu);

    bool getScore() const;
    void setScore(bool score);
    
    bool getEnding() const;
    void setEnding(bool ending);
    
    void showIntro() const;
    void saveScore(int value, std::string player, std::string file);
    
    void showScores(std::string file);
    
};

#endif /* defined(__ShootThemUp__Menu__) */
