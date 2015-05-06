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
Ally::Ally() : Ship(MODEL_WIDTH/2, MODEL_HEIGHT-ALLY_PICTURE_HEIGHT-10, DEFAULT_SHIP_LIFE,ALLY_PICTURE_WIDTH/3, ALLY_PICTURE_HEIGHT, ALLY_SHIP_FIRERATE, ALLY_DEFAULT_SPEEDX, ALLY_DEFAULT_SPEEDY), _numbersOfLife(DEFAULT_NUMBER_OF_LIFE), _score(DEFAULT_SCORE) {}

/*
 * contructor
 * params : x, y and health of ally
 */
//Ally::Ally(const float x, const float y, const int health):Ship(x, y, health,ALLY_PICTURE_HEIGHT, ALLY_PICTURE_WIDTH/3), _numbersOfLife(DEFAULT_NUMBER_OF_LIFE), _score(DEFAULT_SCORE) {}

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
    return _numbersOfLife <= 0;
}

/*
 * returns : string of number life and ship toString
 * info : constant, override
 */
string Ally::toString() const{
    string str = "Notre vaisseau";
    str += "\n";

    str += "\tScore : ";
    #ifdef __linux__
    str += to_string(_score) + "\n";
    #endif

    str += "\tNombre de vie : ";
    #ifdef __linux__
    str += to_string(_numbersOfLife);
    #endif

    str += "\n";

    str += "\tType de missile : ";
    if(_bulletType == 0){
        str += "standard";
    }
    else if(_bulletType == 1){
        str += "boule de feu";
    }
    else if(_bulletType == 2){
        str += "petit laser";
    }
    else if(_bulletType == 3){
        str += "laser";
    }
    str += "\n";

    str += "\tDégat : ";
    if(_bulletType == 0){
    #ifdef __linux__
        str += to_string(MAIN_SHOOT_DAMAGE);
    #endif

    }
    else if(_bulletType == 1){
    #ifdef __linux__
        str += to_string(DEFAULT_FIREBALL_DAMAGE);
    #endif

    }
    else if(_bulletType == 2){
    #ifdef __linux__
        str += to_string(DEFAULT_TINYLASER_DAMAGE);
    #endif

    }
    else if(_bulletType == 3){
    #ifdef __linux__
        str += to_string(DEFAULT_LASER_DAMAGE);
    #endif

    }

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

int Ally::getScore() const{
    return _score;
}

//----------SETTERS----------
/*
 * set the health of ally
 */

/*
 * set number of life
 */
void Ally::setNumberOfLife(int numberOfLive){
    _numbersOfLife = numberOfLive;
}

void Ally::setScore(int expPoint){
    _score += DEFAULT_POINT + expPoint;
}















