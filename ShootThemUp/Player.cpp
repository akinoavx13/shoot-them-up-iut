//
//  Player.cpp
//  ShootThemUp
//
//  Created by Nicolas on 14/04/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Player.h"

using namespace std;

Player::Player(string name, int score) : _name(name), _score(score) {}

Player::Player(const Player &p){
    _name=p._name;
    _score=p._score;
}

Player::~Player(){}

Player Player::getPlayer() const{
    return *this;
}

int Player::getScore() const{
    return _score;
}

bool Player::alreadyExist(Player test) const{
    return _name==test._name;
}

void Player::bestScore(int test){
    if(test>_score){
        _score = test;
    }
}

string Player::toString() const{
    string str = "***********\n" ;
    str += "Name  = " + _name + "\n";
    str += "Score = " + to_string(_score) + "\n\n";
    
    return str;
}