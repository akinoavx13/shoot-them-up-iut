//
//  Player.h
//  ShootThemUp
//
//  Created by Nicolas on 14/04/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__Player__
#define __ShootThemUp__Player__

#include <stdio.h>
#include <string>

class Player {
    private :
        std::string _name;
        int _score;

    public:
        Player(std::string name, int score);
        Player(Player* &p);
        ~Player();

        int getScore() const;
        std::string getName() const;

        bool alreadyExist(Player* &test) const;

        void bestScore(int test);

        std::string toString() const;
};

#endif /* defined(__ShootThemUp__Player__) */
