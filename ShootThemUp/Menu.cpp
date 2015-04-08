//
//  Menu.cpp
//  ShootThemUp
//
//  Created by Nicolas on 30/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Menu.h"


using namespace std;

Menu::Menu() : _intro(true), _game(false), _level(false), _shop(false), _menu(false), _score(false) {}

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

void Menu::setEnding(bool ending){
    _ending = ending;
}

void Menu::showIntro() const{
    
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