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

}

void GraphicLibrary::loadLibrary(){
    Image img0;
    Sprite sp0;
    if(img0.LoadFromFile("sprites/background.png")){
        _imagesList.push_back(img0);
        sp0.SetImage(img0);
        _spritesList.push_back(sp0);
    }

    Image img1;
    Sprite sp1;
    if(img1.LoadFromFile("ShootThemUp/sprites/boss.png")){
        _imagesList.push_back(img1);
        sp1.SetImage(img1);
        _spritesList.push_back(sp1);
    }

    Image img2;
    Sprite sp2;
    if(img2.LoadFromFile("ShootThemUp/sprites/credits.png")){
        _imagesList.push_back(img2);
        sp2.SetImage(img2);
        _spritesList.push_back(sp2);
    }

    Image img3;
    Sprite sp3;
    if(img3.LoadFromFile("ShootThemUp/sprites/cursor.png")){
        _imagesList.push_back(img3);
        sp3.SetImage(img3);
        _spritesList.push_back(sp3);
    }

    Image img4;
    Sprite sp4;
    if(img4.LoadFromFile("ShootThemUp/sprites/doublePetitLaser.png")){
        _imagesList.push_back(img4);
        sp3.SetImage(img4);
        _spritesList.push_back(sp4);
    }

    Image img5;
    Sprite sp5;
    if(img5.LoadFromFile("ShootThemUp/sprites/fireBall.png")){
        _imagesList.push_back(img5);
        sp5.SetImage(img5);
        _spritesList.push_back(sp5);
    }

    Image img6;
    Sprite sp6;
    if(img6.LoadFromFile("ShootThemUp/sprites/gameOver.png")){
        _imagesList.push_back(img6);
        sp6.SetImage(img6);
        _spritesList.push_back(sp6);
    }

    Image img7;
    Sprite sp7;
    if(img7.LoadFromFile("ShootThemUp/sprites/getReady.png")){
        _imagesList.push_back(img7);
        sp7.SetImage(img7);
        _spritesList.push_back(sp7);
    }

    Image img8;
    Sprite sp8;
    if(img8.LoadFromFile("ShootThemUp/sprites/grosseExplosion.png")){
        _imagesList.push_back(img8);
        sp8.SetImage(img8);
        _spritesList.push_back(sp8);
    }

    Image img9;
    Sprite sp9;
    if(img9.LoadFromFile("ShootThemUp/sprites/wave.png")){
        _imagesList.push_back(img9);
        sp9.SetImage(img9);
        _spritesList.push_back(sp9);
    }

    Image img10;
    Sprite sp10;
    if(img10.LoadFromFile("ShootThemUp/sprites/tiny.png")){
        _imagesList.push_back(img10);
        sp10.SetImage(img10);
        _spritesList.push_back(sp10);
    }

    Image img11;
    Sprite sp11;
    if(img11.LoadFromFile("ShootThemUp/sprites/submarine.png")){
        _imagesList.push_back(img11);
        sp11.SetImage(img11);
        _spritesList.push_back(sp11);
    }

    Image img12;
    Sprite sp12;
    if(img12.LoadFromFile("ShootThemUp/sprites/standard.png")){
        _imagesList.push_back(img12);
        sp12.SetImage(img12);
        _spritesList.push_back(sp12);
    }

    Image img13;
    Sprite sp13;
    if(img13.LoadFromFile("ShootThemUp/sprites/scoring.png")){
        _imagesList.push_back(img13);
        sp13.SetImage(img13);
        _spritesList.push_back(sp13);
    }

    Image img14;
    Sprite sp14;
    if(img14.LoadFromFile("ShootThemUp/sprites/quit.png")){
        _imagesList.push_back(img14);
        sp14.SetImage(img14);
        _spritesList.push_back(sp14);
    }

    Image img15;
    Sprite sp15;
    if(img15.LoadFromFile("ShootThemUp/sprites/play.png")){
        _imagesList.push_back(img15);
        sp15.SetImage(img15);
        _spritesList.push_back(sp15);
    }

    Image img16;
    Sprite sp16;
    if(img16.LoadFromFile("ShootThemUp/sprites/score.png")){
        _imagesList.push_back(img16);
        sp16.SetImage(img16);
        _spritesList.push_back(sp16);
    }

    Image img17;
    Sprite sp17;
    if(img17.LoadFromFile("ShootThemUp/sprites/player.png")){
        _imagesList.push_back(img17);
        sp17.SetImage(img17);
        _spritesList.push_back(sp15);
    }

    Image img18;
    Sprite sp18;
    if(img18.LoadFromFile("ShootThemUp/sprites/petitLaser.png")){
        _imagesList.push_back(img18);
        sp18.SetImage(img18);
        _spritesList.push_back(sp18);
    }

    Image img19;
    Sprite sp19;
    if(img19.LoadFromFile("ShootThemUp/sprites/petiteExplosion.png")){
        _imagesList.push_back(img19);
        sp19.SetImage(img19);
        _spritesList.push_back(sp19);
    }

    Image img20;
    Sprite sp20;
    if(img20.LoadFromFile("ShootThemUp/sprites/options.png")){
        _imagesList.push_back(img20);
        sp20.SetImage(img20);
        _spritesList.push_back(sp20);
    }

    Image img21;
    Sprite sp21;
    if(img21.LoadFromFile("ShootThemUp/sprites/mighty.png")){
        _imagesList.push_back(img21);
        sp21.SetImage(img21);
        _spritesList.push_back(sp21);
    }

    Image img22;
    Sprite sp22;
    if(img22.LoadFromFile("ShootThemUp/sprites/menuIntro.png")){
        _imagesList.push_back(img22);
        sp22.SetImage(img22);
        _spritesList.push_back(sp22);
    }

    Image img23;
    Sprite sp23;
    if(img23.LoadFromFile("ShootThemUp/sprites/laser.png")){
        _imagesList.push_back(img23);
        sp23.SetImage(img23);
        _spritesList.push_back(sp23);
    }

    Image img24;
    Sprite sp24;
    if(img24.LoadFromFile("ShootThemUp/sprites/highScores.png")){
        _imagesList.push_back(img24);
        sp6.SetImage(img24);
        _spritesList.push_back(sp24);
    }
}

Image GraphicLibrary::getImage(int i) const{
    return _imagesList[i];
}

Sprite GraphicLibrary::getSprite(int i) const{
    return _spritesList[i];
}
