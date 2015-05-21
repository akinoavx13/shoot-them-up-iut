//
//  Player.cpp
//  ShootThemUp
//
//  Created by Nicolas on 14/04/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Player.h"
#include <iostream>

using namespace std;

/*
 * CONSTRUCTOR
 */
Player::Player(string name, int score) : _name(name), _score(score) {}

Player::Player(Player* &p) : _name(p->_name), _score(p->_score) {}

/*
 * DESTRUCTOR
 */
Player::~Player(){}

/*
 * METHODS
 */
//check if the player his in the score file
bool Player::alreadyExist(Player* &test) const{
    return _name == test->_name;
}

//best score of the game
void Player::bestScore(int test){
    if(test > _score){
        _score = test;
    }
}

//write somme informations about score
string Player::toString() const{
    string str = "***********\n" ;
    str += "Name  = " + _name + "\n";
#ifdef __linux__
    str += "Score = " + to_string(_score) + "\n\n";
#endif
    return str;
}

/*
 * GETTERS
 */
string Player::getName() const{
    return _name;
}

int Player::getScore() const{
    return _score;
}
