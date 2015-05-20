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

    bool getSaveScore() const;
    void setSaveScore(bool saveScore);

    bool getEnding() const;
    void setEnding(bool ending);

    bool getReady() const;
    void setReady(bool ready);

    bool getOptions() const;
    void setOption(bool options);

    bool getCredits() const;
    void setCredits(bool credits);

    int getTheme() const;
    void setTheme(int theme);

    std::string getLanguage() const;
    void setLanguage(std::string language);

    void showIntroTerminal() const;
    void saveScore(int value, std::string player, std::string file);

    std::vector<Player*> showScores(std::string file);

};

#endif /* defined(__ShootThemUp__Menu__) */
