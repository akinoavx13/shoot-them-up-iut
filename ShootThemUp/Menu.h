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
#include <vector>

#include "Player.h"

class Menu {
    
private:
    
    bool _intro;
    bool _game;
    bool _level;
    bool _shop;
    bool _menu;
    bool _score;
    bool _saveScore;
    bool _ending;
    bool _readyToPlay;
    bool _options;
    bool _credits;

    std::string _language;
    
    int _theme;

public:
    
    //CONSTRUCTOR
    Menu();
    
    //DESTRUCTOR
    ~Menu();
    
    //METHODS
    void showIntroTerminal() const;
    void saveScore(int value, std::string player, std::string file);
    std::vector<Player*> showScores(std::string file);

    //GETTERS
    bool getIntro() const;
    bool getGame() const;
    bool getLevel() const;
    bool getShop() const;
    bool getMenu() const;
    bool getScore() const;
    bool getSaveScore() const;
    bool getEnding() const;
    bool getReady() const;
    bool getOptions() const;
    bool getCredits() const;
    int getTheme() const;
    std::string getLanguage() const;

    //SETTERS
    void setIntro(bool intro);
    void setGame(bool shop);
    void setLevel(bool level);
    void setShop(bool shop);
    void setMenu(bool menu);
    void setScore(bool score);
    void setSaveScore(bool saveScore);
    void setEnding(bool ending);
    void setReady(bool ready);
    void setOption(bool options);
    void setCredits(bool credits);
    void setTheme(int theme);
    void setLanguage(std::string language);

};

#endif /* defined(__ShootThemUp__Menu__) */
