//
//  Menu.cpp
//  ShootThemUp
//
//  Created by Nicolas on 30/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Menu.h"
#include <fstream>
#include <vector>

using namespace std;

Menu::Menu() : _intro(true), _game(false), _level(false), _shop(false), _menu(false), _score(false), _saveScore(false), _ending(false) {}

Menu::~Menu(){}

//GETTERS
bool Menu::getIntro() const{
    return _intro;
}

bool Menu::getGame() const{
    return _game;
}

bool Menu::getLevel() const{
    return _level;
}

bool Menu::getShop() const{
    return _shop;
}

bool Menu::getMenu() const{
    return _menu;
}

bool Menu::getScore() const{
    return _score;
}

bool Menu::getSaveScore() const{
    return _saveScore;
}

bool Menu::getEnding() const{
    return _ending;
}

//SETTERS
void Menu::setIntro(bool intro){
    _intro = intro;
}

void Menu::setGame(bool game){
    _game = game;
}

void Menu::setLevel(bool level){
    _level = level;
}

void Menu::setShop(bool shop){
    _shop = shop;
}

void Menu::setMenu(bool menu){
    _menu = menu;
}

void Menu::setScore(bool score){
    _score = score;
}

void Menu::setSaveScore(bool saveScore){
    _saveScore = saveScore;
}

void Menu::setEnding(bool ending){
    _ending = ending;
}

void Menu::showIntroTerminal() const{

    cout << "==================================================================" << endl;
    cout << "*                                                                *" << endl;
    cout << "*      _____                                          _____      *" << endl;
    cout << "*     |         |      |    ||     ||    |       |   |     |     *" << endl;
    cout << "*    |          |      |    | |   | |    |       |   |      |    *" << endl;
    cout << "*     |___      |      |    |  |_|  |    |       |   | ____|     *" << endl;
    cout << "*         |     |------|    |       |    |       |   |           *" << endl;
    cout << "*          |    |      |    |       |    |       |   |           *" << endl;
    cout << "*    _____|     |      |    |       |     |_____|    |           *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "==================================================================" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                 Maxime Maheo & Nicolas Valaise                 *" << endl;
    cout << "*                                                                *" << endl;
    cout << "==================================================================" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*             x                                                  *" << endl;
    cout << "*                          x           x                         *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                          |                                     *" << endl;
    cout << "*                    x                                           *" << endl;
    cout << "*                          |                                     *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                               |                                *" << endl;
    cout << "*                                                                *" << endl;
    cout << "*                             =====                              *" << endl;
    cout << "*                                                                *" << endl;
    cout << "==================================================================" << endl;

}

void Menu::saveScore(int value, string player, string file){
    fstream f;
    
    #ifdef __linux__
        f.open(file,ios::out|ios::app);
    #else
        f.open(file.c_str(),ios::out|ios::app);
    #endif

    if(!f.fail()) {
        f << player;
        f << value;
        f << "\n" ;

        f.close();
    }
    else {
        cout << "Oups, the file can't be opened ..." << endl;
    }
}

vector<Player*> Menu::showScores(string file){
    fstream f;

    vector<Player*> players;

    #ifdef __linux__
        f.open(file, ios::in);
    #else
        f.open(file.c_str(), ios::in);
    #endif
    if(!f.fail()){
        while(!f.eof()){
            string name;
            string space;
            int score;

            f >> name;
            f >> score;

            Player* p = new Player(name, score);

            bool exist = false;

            for(auto test : players){
                if(test->alreadyExist(p)){
                    test->bestScore(p->getScore());
                    exist=true;
                }
            }

            if(!exist && name.length()>0) {
                players.push_back(p);
            }
        }

        for(int i = 0; i <players.size(); i++){
            for(int j = i; j <players.size(); j ++){
                if(players[i]->getScore() < players[j]->getScore()){
                    Player* temp = new Player(players[i]);
                    players[i] = players[j];
                    players[j] = temp;
                }
            }
        }
    }
    else {
        cout << "Oups, the file can't be opened ..." << endl;
    }
    return players;

}
