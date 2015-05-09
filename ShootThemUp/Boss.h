//
//  Boss.h
//  ShootThemUp
//
//  Created by Nicolas on 30/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#ifndef __ShootThemUp__Boss__
#define __ShootThemUp__Boss__

#include <stdio.h>
#include <iostream>

#include "Enemy.h"
#include "Ship.h"

class Boss : public Enemy{
private:

public:
    Boss();
    Boss(const float x, const float y, const int health, const float firerate);

    ~Boss();

    std::string toString() const override;

};

#endif /* defined(__ShootThemUp__Boss__) */
