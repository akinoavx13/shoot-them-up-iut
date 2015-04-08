//
//  Ally.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 18/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "Ally.h"
#include "Level.h"

using namespace std;

/*
 * default constructor
 */
Ally::Ally() : _numbersOfLife(DEFAULT_NUMBER_OF_LIFE), _score(DEFAULT_SCORE) {}

/*
 * contructor
 * params : x, y and health of ally
 */
Ally::Ally(const float x, const float y, const int health):Ship(x, y, health), _numbersOfLife(DEFAULT_NUMBER_OF_LIFE), _score(DEFAULT_SCORE) {}

/*
 * destructor
 * info : virtual
 */
Ally::~Ally(){

    cout << "Player delete" << endl;

}

//----------METHODS----------
/*
 * returns : true if the player has more life
 * info : constant
 */
bool Ally::isOver() const{
    return _numbersOfLife == 0;
}

/*
 * returns : string of number life and ship toString
 * info : constant, override
 */
string Ally::toString() const{
    string str = "Notre vaisseau";
    str += "\n";

    str += "\Score : ";
    str += to_string(_score) + "\n";
    
    str += "\tNombre de vie : ";
    str += to_string(_numbersOfLife);
    str += "\n";

    str += Ship::toString();
    return str;
}

//----------GETTERS----------
/*
 * returns : number of life
 * info : constant
 */
int Ally::getNumberOfLife() const{
    return _numbersOfLife;
}

//----------SETTERS----------
/*
 * set the health of ally
 */
void Ally::setHealth(int health){
    _health = health;
}

/*
 * set number of life
 */
void Ally::setNumberOfLife(int numberOfLive){
    _numbersOfLife = numberOfLive;
}

void Ally::setPoint(int expPoint){
    _score += DEFAULT_POINT + expPoint;
}















