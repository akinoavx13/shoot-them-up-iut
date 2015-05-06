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
    for(auto img : _imagesList)
    {
        delete img;
    }
    _imagesList.clear();
}

void GraphicLibrary::loadLibrary(){
    Image * img0 = new Image();
    if(img0->LoadFromFile("ShootThemUp/sprites/background.png")){
        _imagesList.push_back(img0);
    }

    Image * img1 = new Image();
    if(img1->LoadFromFile("ShootThemUp/sprites/boss.png")){
        _imagesList.push_back(img1);
    }

    Image * img2 = new Image();
    if(img2->LoadFromFile("ShootThemUp/sprites/credits.png")){
        _imagesList.push_back(img2);
    }

    Image * img3 = new Image();
    if(img3->LoadFromFile("ShootThemUp/sprites/cursor.png")){
        _imagesList.push_back(img3);
    }

    Image * img4 = new Image();
    if(img4->LoadFromFile("ShootThemUp/sprites/doublePetitLaser.png")){
        _imagesList.push_back(img4);
    }

    Image * img5 = new Image();
    if(img5->LoadFromFile("ShootThemUp/sprites/fireBall.png")){
        _imagesList.push_back(img5);

    }

    Image * img6 = new Image();
    if(img6->LoadFromFile("ShootThemUp/sprites/gameOver.png")){
        _imagesList.push_back(img6);
    }

    Image * img7 = new Image();
    if(img7->LoadFromFile("ShootThemUp/sprites/getReady.png")){
        _imagesList.push_back(img7);
    }

    Image * img8 = new Image();
    if(img8->LoadFromFile("ShootThemUp/sprites/grosseExplosion.png")){
        _imagesList.push_back(img8);
    }

    Image * img9 = new Image();
    if(img9->LoadFromFile("ShootThemUp/sprites/wave.png")){
        _imagesList.push_back(img9);
    }

    Image * img10 = new Image();
    if(img10->LoadFromFile("ShootThemUp/sprites/tiny.png")){
        _imagesList.push_back(img10);
    }

    Image * img11 = new Image();
    if(img11->LoadFromFile("ShootThemUp/sprites/submarine.png")){
        _imagesList.push_back(img11);
    }

    Image * img12 = new Image();
    if(img12->LoadFromFile("ShootThemUp/sprites/standard.png")){
        _imagesList.push_back(img12);
    }

    Image * img13 = new Image();
    if(img13->LoadFromFile("ShootThemUp/sprites/scoring.png")){
        _imagesList.push_back(img13);
    }

    Image * img14 = new Image();
    if(img14->LoadFromFile("ShootThemUp/sprites/quit.png")){
        _imagesList.push_back(img14);
    }

    Image * img15 = new Image();
    if(img15->LoadFromFile("ShootThemUp/sprites/play.png")){
        _imagesList.push_back(img15);
    }

    Image * img16 = new Image();
    if(img16->LoadFromFile("ShootThemUp/sprites/score.png")){
        _imagesList.push_back(img16);
    }

    Image * img17 = new Image();
    if(img17->LoadFromFile("ShootThemUp/sprites/player.png")){
        _imagesList.push_back(img17);
    }

    Image * img18 = new Image();
    if(img18->LoadFromFile("ShootThemUp/sprites/petitLaser.png")){
        _imagesList.push_back(img18);
    }

    Image * img19 = new Image();
    if(img19->LoadFromFile("ShootThemUp/sprites/petiteExplosion.png")){
        _imagesList.push_back(img19);
    }

    Image * img20 = new Image();
    if(img20->LoadFromFile("ShootThemUp/sprites/options.png")){
        _imagesList.push_back(img20);
    }

    Image * img21 = new Image();
    if(img21->LoadFromFile("ShootThemUp/sprites/mighty.png")){
        _imagesList.push_back(img21);
    }

    Image * img22 = new Image();
    if(img22->LoadFromFile("ShootThemUp/sprites/menuIntro.png")){
        _imagesList.push_back(img22);
    }

    Image * img23 = new Image();
    if(img23->LoadFromFile("ShootThemUp/sprites/laser.png")){
        _imagesList.push_back(img23);
    }

    Image * img24 = new Image();
    if(img24->LoadFromFile("ShootThemUp/sprites/highScores.png")){
        _imagesList.push_back(img24);
    }
}

Image * GraphicLibrary::getImage(int i) const{
    return _imagesList[i];
}
