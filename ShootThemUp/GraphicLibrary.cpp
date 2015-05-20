//
//  GameViewSFML.h
//  ShootThemUp
//
//  Created by Nicolas on 28/04/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#include "GraphicLibrary.h"

using namespace sf;

GraphicLibrary::GraphicLibrary(){

}

GraphicLibrary::~GraphicLibrary(){
    for (int i = 0; i < _imagesList.size(); i++) {
        delete _imagesList[i];
    }
    _imagesList.clear();
}

void GraphicLibrary::loadLibrary(){
    Image * img0 = new Image();
    #ifdef __linux__
    if(img0->LoadFromFile("ShootThemUp/sprites/background.png")){
    #else
    if(img0->LoadFromFile("background.png")){
    #endif
        _imagesList.push_back(img0);
    }

    Image * img1 = new Image();
    #ifdef __linux__
    if(img1->LoadFromFile("ShootThemUp/sprites/boss.png")){
    #else
    if(img1->LoadFromFile("boss.png")){
    #endif
        _imagesList.push_back(img1);
    }

    Image * img2 = new Image();
    #ifdef __linux__
    if(img2->LoadFromFile("ShootThemUp/sprites/credits.png")){
    #else
    if(img2->LoadFromFile("credits.png")){
    #endif
        _imagesList.push_back(img2);
    }

    Image * img3 = new Image();
    #ifdef __linux__
    if(img3->LoadFromFile("ShootThemUp/sprites/cursor.png")){
    #else
    if(img3->LoadFromFile("cursor.png")){
    #endif
        _imagesList.push_back(img3);
    }

    Image * img4 = new Image();
    #ifdef __linux__
    if(img4->LoadFromFile("ShootThemUp/sprites/doublePetitLaser.png")){
    #else
    if(img4->LoadFromFile("doublePetitLaser.png")){
    #endif
        _imagesList.push_back(img4);
    }

    Image * img5 = new Image();
    #ifdef __linux__
    if(img5->LoadFromFile("ShootThemUp/sprites/fireBall.png")){
    #else
    if(img5->LoadFromFile("fireBall.png")){
    #endif
        _imagesList.push_back(img5);

    }

    Image * img6 = new Image();
    #ifdef __linux__
    if(img6->LoadFromFile("ShootThemUp/sprites/gameOver.png")){
    #else
    if(img6->LoadFromFile("gameOver.png")){
    #endif
        _imagesList.push_back(img6);
    }

    Image * img7 = new Image();
    #ifdef __linux__
    if(img7->LoadFromFile("ShootThemUp/sprites/getReady.png")){
    #else
    if(img7->LoadFromFile("getReady.png")){
    #endif
        img7->CreateMaskFromColor(Color(0, 0, 0));
        _imagesList.push_back(img7);
    }

    Image * img8 = new Image();
    #ifdef __linux__
    if(img8->LoadFromFile("ShootThemUp/sprites/grosseExplosion.png")){
    #else
    if(img8->LoadFromFile("grosseExplosion.png")){
    #endif
        _imagesList.push_back(img8);
    }

    Image * img9 = new Image();
    #ifdef __linux__
    if(img9->LoadFromFile("ShootThemUp/sprites/wave.png")){
    #else
    if(img9->LoadFromFile("wave.png")){
    #endif
        _imagesList.push_back(img9);
    }

    Image * img10 = new Image();
    #ifdef __linux__
    if(img10->LoadFromFile("ShootThemUp/sprites/tiny.png")){
    #else
    if(img10->LoadFromFile("tiny.png")){
    #endif
        _imagesList.push_back(img10);
    }

    Image * img11 = new Image();
    #ifdef __linux__
    if(img11->LoadFromFile("ShootThemUp/sprites/submarine.png")){
    #else
    if(img11->LoadFromFile("submarine.png")){
    #endif
        _imagesList.push_back(img11);
    }

    Image * img12 = new Image();
    #ifdef __linux__
    if(img12->LoadFromFile("ShootThemUp/sprites/standard.png")){
    #else
    if(img12->LoadFromFile("standard.png")){
    #endif
        _imagesList.push_back(img12);
    }

    Image * img13 = new Image();
    #ifdef __linux__
    if(img13->LoadFromFile("ShootThemUp/sprites/scoring.png")){
    #else
    if(img13->LoadFromFile("scoring.png")){
    #endif
        _imagesList.push_back(img13);
    }

    Image * img14 = new Image();
    #ifdef __linux__
    if(img14->LoadFromFile("ShootThemUp/sprites/quit.png")){
    #else
    if(img14->LoadFromFile("quit.png")){
    #endif
        _imagesList.push_back(img14);
    }

    Image * img15 = new Image();
    #ifdef __linux__
    if(img15->LoadFromFile("ShootThemUp/sprites/play.png")){
    #else
    if(img15->LoadFromFile("play.png")){
    #endif
        _imagesList.push_back(img15);
    }

    Image * img16 = new Image();
    #ifdef __linux__
    if(img16->LoadFromFile("ShootThemUp/sprites/score.png")){
    #else
    if(img16->LoadFromFile("score.png")){
    #endif
        _imagesList.push_back(img16);
    }

    Image * img17 = new Image();
    #ifdef __linux__
    if(img17->LoadFromFile("ShootThemUp/sprites/player.png")){
    #else
    if(img17->LoadFromFile("player.png")){
    #endif
        _imagesList.push_back(img17);
    }

    Image * img18 = new Image();
    #ifdef __linux__
    if(img18->LoadFromFile("ShootThemUp/sprites/petitLaser.png")){
    #else
    if(img18->LoadFromFile("petitLaser.png")){
    #endif
        _imagesList.push_back(img18);
    }

    Image * img19 = new Image();
    #ifdef __linux__
    if(img19->LoadFromFile("ShootThemUp/sprites/petiteExplosion.png")){
    #else
    if(img19->LoadFromFile("petiteExplosion.png")){
    #endif
        _imagesList.push_back(img19);
    }

    Image * img20 = new Image();
    #ifdef __linux__
    if(img20->LoadFromFile("ShootThemUp/sprites/options.png")){
    #else
    if(img20->LoadFromFile("options.png")){
    #endif
        _imagesList.push_back(img20);
    }

    Image * img21 = new Image();
    #ifdef __linux__
    if(img21->LoadFromFile("ShootThemUp/sprites/mighty.png")){
    #else
    if(img21->LoadFromFile("mighty.png")){
    #endif
        _imagesList.push_back(img21);
    }

    Image * img22 = new Image();
    #ifdef __linux__
    if(img22->LoadFromFile("ShootThemUp/sprites/menuIntro.png")){
    #else
    if(img22->LoadFromFile("menuIntro.png")){
    #endif
        _imagesList.push_back(img22);
    }

    Image * img23 = new Image();
    #ifdef __linux__
    if(img23->LoadFromFile("ShootThemUp/sprites/laser.png")){
    #else
    if(img23->LoadFromFile("laser.png")){
    #endif
        _imagesList.push_back(img23);
    }

    Image * img24 = new Image();
    #ifdef __linux__
    if(img24->LoadFromFile("ShootThemUp/sprites/highScores.png")){
    #else
    if(img24->LoadFromFile("highScores.png")){
    #endif
        _imagesList.push_back(img24);
    }

    Image * img25 = new Image();
    #ifdef __linux__
    if(img25->LoadFromFile("ShootThemUp/sprites/coeur.png")){
    #else
    if(img25->LoadFromFile("coeur.png")){
    #endif
        _imagesList.push_back(img25);
    }

    Image * img26 = new Image();
    #ifdef __linux__
    if(img26->LoadFromFile("ShootThemUp/sprites/backgroundShop.png")){
    #else
    if(img26->LoadFromFile("backgroundShop.png")){
    #endif
        _imagesList.push_back(img26);
    }

    Image * img27 = new Image();
    #ifdef __linux__
    if(img27->LoadFromFile("ShootThemUp/sprites/ennemy_0.png")){
    #else
    if(img27->LoadFromFile("ennemy_0.png")){
    #endif
        _imagesList.push_back(img27);
    }

    Image * img28 = new Image();
    #ifdef __linux__
    if(img28->LoadFromFile("ShootThemUp/sprites/ennemy_1.png")){
    #else
    if(img28->LoadFromFile("ennemy_1.png")){
    #endif
        _imagesList.push_back(img28);
    }
    Image * img29 = new Image();
    #ifdef __linux__
    if(img29->LoadFromFile("ShootThemUp/sprites/ennemy_2.png")){
    #else
    if(img29->LoadFromFile("ennemy_2.png")){
    #endif
        _imagesList.push_back(img29);
    }

    Image * img30 = new Image();
    #ifdef __linux__
    if(img30->LoadFromFile("ShootThemUp/sprites/ship_all.png")){
    #else
    if(img30->LoadFromFile("ship_all.png")){
    #endif
        _imagesList.push_back(img30);
    }

    Image * img31 = new Image();
    #ifdef __linux__
    if(img31->LoadFromFile("ShootThemUp/sprites/shot.png")){
    #else
    if(img31->LoadFromFile("shot.png")){
    #endif
        _imagesList.push_back(img31);
    }

    Image * img32 = new Image();
    #ifdef __linux__
    if(img32->LoadFromFile("ShootThemUp/sprites/logo.jpeg")){
    #else
    if(img32->LoadFromFile("logo.jpeg")){
    #endif
        _imagesList.push_back(img32);
    }
}

Image * GraphicLibrary::getImage(int i) const{
    return _imagesList[i];
}
