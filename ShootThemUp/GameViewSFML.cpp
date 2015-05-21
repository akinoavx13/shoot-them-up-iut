//
//  GameViewSFML.cpp
//  ShootThemUp
//
//  Created by Nicolas on 28/04/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#include "GameViewSFML.h"
#include "const.h"
#include "Picture.h"
#include <sstream>

using namespace sf;


#include <iostream>
using namespace std;

GameViewSFML::GameViewSFML():_yBackground(0), _yBackground2(-SCREEN_HEIGHT + 2){
    _menu = new Menu();
    _window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Shoot Them Up");
    _window->SetFramerateLimit(SCREEN_FPS);
    #ifdef __linux__
    _gameModel = nullptr;
    if (!buffer1.LoadFromFile("ShootThemUp/shoot.wav"))
    {
        cout << "The sound can't be load" << endl;
    }else{
        sound_shoot.SetBuffer(buffer1);
        sound_shoot.SetPitch(1.5f);
        sound_shoot.SetVolume(75.f);
    }

    if (!buffer2.LoadFromFile("ShootThemUp/bonusShoot.wav"))
    {
        cout << "The sound can't be load" << endl;
    }else{
        sound_bonusShoot.SetBuffer(buffer2);
        sound_bonusShoot.SetPitch(1.5f);
        sound_bonusShoot.SetVolume(75.f);
    }

    if (!buffer3.LoadFromFile("ShootThemUp/pieces.wav"))
    {
        cout << "The sound can't be load" << endl;
    }else{
        sound_iziMoney.SetBuffer(buffer3);
        sound_iziMoney.SetPitch(1.5f);
        sound_iziMoney.SetVolume(75.f);
    }
    if(!font.LoadFromFile("ShootThemUp/police.ttf")){
        cout << "The font can't be load" << endl;
    }
    #else
    _gameModel = 0;
    if (!buffer1.LoadFromFile("shoot.wav"))
    {
        cout << "The sound can't be load" << endl;
    }else{
        sound_shoot.SetBuffer(buffer1);
        sound_shoot.SetPitch(1.5f);
        sound_shoot.SetVolume(75.f);
    }

    if (!buffer2.LoadFromFile("bonusShoot.wav"))
    {
        cout << "The sound can't be load" << endl;
    }else{
        sound_bonusShoot.SetBuffer(buffer2);
        sound_bonusShoot.SetPitch(1.5f);
        sound_bonusShoot.SetVolume(75.f);
    }

    if (!buffer3.LoadFromFile("pieces.wav"))
    {
        cout << "The sound can't be load" << endl;
    }else{
        sound_iziMoney.SetBuffer(buffer3);
        sound_iziMoney.SetPitch(1.5f);
        sound_iziMoney.SetVolume(75.f);
    }
    if(!font.LoadFromFile("police.ttf")){
        cout << "The font can't be load" << endl;
    }
    #endif
    _graphicLibrary = new GraphicLibrary();
    _graphicLibrary->loadLibrary();
    time.Reset();



    _letterPut = true;
    _mouseClicked = false;

}

GameViewSFML::~GameViewSFML(){
    delete _menu;
    delete _window;
    delete _graphicLibrary;
}

void GameViewSFML::setModel(GameModel* gameModel){
    _gameModel = gameModel;
}

void GameViewSFML::setModelMenu(){
    _gameModel->setMenu(_menu);
}

void GameViewSFML::draw(){
    //use input for know :
    // - where is the mouse
    // - is one key is down, and which
    const Input& input = _window->GetInput();
    int mouseX = input.GetMouseX();
    int mouseY = input.GetMouseY();

    //check different color in fonction choosen theme
    const int white = 0;
    const int black = 1;
    int col = 0;
    if(_menu->getTheme()==0){
            col = white;
    }
    else if (_menu->getTheme()==1){
        col = black;
    }

    _window->Clear();
    if(_menu->getIntro())
    {
        _window->Clear(Color(0,99,191));

        //into picture
        Picture bg(_graphicLibrary->getImage(22), 0,SCREEN_HEIGHT/3,SCREEN_WIDTH,SCREEN_HEIGHT/3);
        _window->Draw(bg.getSprite());
    }

    else if(_menu->getMenu())
    {
        if(_menu->getTheme() == 0){ //add shape
            _window->Clear(Color(0,99,191));
            addShape(100, 150, 295, 150, 295, 180, 100, 180, false, true, 2, 1);
            if(mouseX > 100 && mouseX < 295 && mouseY > 150 && mouseY < 180){
                addShape(100, 150, 295, 150, 295, 180, 100, 180, true, false, 0, 3);
            }

            addShape(100, 200, 200, 200, 200, 230, 100, 230, false, true, 2, 1);
            if(mouseX > 100 && mouseX < 200 && mouseY > 200 && mouseY < 230){
                addShape(100, 200, 200, 200, 200, 230, 100, 230, true, false, 0, 3);
            }

            addShape(100, 300, 200, 300, 200, 330, 100, 330, false, true, 2, 1);
            if(mouseX > 100 && mouseX < 200 && mouseY > 300 && mouseY < 330){
                addShape(100, 300, 200, 300, 200, 330, 100, 330, true, false, 0, 3);
            }

            addShape(100, 350, 295, 350, 295, 380, 100, 380, false, true, 2, 1);
            if(mouseX > 100 && mouseX < 295 && mouseY > 350 && mouseY < 380){
                addShape(100, 350, 295, 350, 295, 380, 100, 380, true, false, 0, 3);
            }

            addShape(100, 550, 220, 550, 220, 580, 100, 580, false, true, 2, 1);
            if(mouseX > 100 && mouseX < 220 && mouseY > 550 && mouseY < 580){
                addShape(100, 550, 220, 550, 220, 580, 100, 580, true, false, 0, 4);
            }
        }
        else if(_menu->getTheme() == 1){// add pictures
            _window->Clear(Color(255,255,255));

            Picture ally(_graphicLibrary->getImage(37), 300,400,190, 200);
            _window->Draw(ally.getSprite());

            //buttom picture
            Picture shape1(_graphicLibrary->getImage(36), 90,150,420, 30, 0,0, 150, 80);
            _window->Draw(shape1.getSprite());
            if(mouseX > 100 && mouseX < 295 && mouseY > 150 && mouseY < 180){
                Picture shape1(_graphicLibrary->getImage(36), 90,150,420, 30, 150,0, 300, 80);
                _window->Draw(shape1.getSprite());
            }

            Picture shape2(_graphicLibrary->getImage(36), 90,200,250, 30, 0,0, 150, 80);
            _window->Draw(shape2.getSprite());
            if(mouseX > 100 && mouseX < 200 && mouseY > 200 && mouseY < 230){
                Picture shape2(_graphicLibrary->getImage(36), 90,200,250, 30, 150,0, 300, 80);
                _window->Draw(shape2.getSprite());
            }

            Picture shape3(_graphicLibrary->getImage(36), 90,300,250, 30, 0,0, 150, 80);
            _window->Draw(shape3.getSprite());
            if(mouseX > 100 && mouseX < 200 && mouseY > 300 && mouseY < 330){
                Picture shape3(_graphicLibrary->getImage(36), 90,300,250, 30, 150,0, 300, 80);
                _window->Draw(shape3.getSprite());
            }

            Picture shape4(_graphicLibrary->getImage(36), 90,350,420, 30, 0,0, 150, 80);
            _window->Draw(shape4.getSprite());
            if(mouseX > 100 && mouseX < 295 && mouseY > 350 && mouseY < 380){
                Picture shape4(_graphicLibrary->getImage(36), 90,350,420, 30,150,0, 300, 80);
                _window->Draw(shape4.getSprite());
            }

            Picture shape5(_graphicLibrary->getImage(36), 90,550,250, 30, 0,0, 150, 80);
            _window->Draw(shape5.getSprite());
            if(mouseX > 100 && mouseX < 220 && mouseY > 550 && mouseY < 580){
                Picture shape5(_graphicLibrary->getImage(36), 90,550,250, 30, 150,0, 300, 80);
                _window->Draw(shape5.getSprite());
            }
        }
        if(_menu->getLanguage() == "english"){
            addText("PLAY GAME", 110, 155, 20, col);
            addText("OPTIONS", 110, 205, 20, col);
            addText("CREDITS", 110, 305, 20, col);
            addText("HIGHT SCORES", 110, 355, 20, col);
            addText("QUIT", 110, 555, 20, col);
        }
        else if (_menu->getLanguage() == "francais"){
            addText("LANCER LE JEUX", 110, 155, 20, col);
            addText("OPTIONS", 110, 205, 20, col);
            addText("CREDITS", 110, 305, 20, col);
            addText("MEILLEUR SCORES", 110, 355, 20,col);
            addText("QUITTER", 110, 555, 20, col);
        }
        else if(_menu->getLanguage() == "deutsch"){
            addText("SPIEL SPIELEN", 110, 155, 20, col);
            addText("OPTIONEN", 110, 205, 20, col);
            addText("CREDITS", 110, 305, 20,col);
            addText("HIGHSCORES", 110, 355, 20,col);
            addText("VERLASSEN", 110, 555, 20,col);
        }
        time.Reset();
    }
    else if(_menu->getGame())
    {
        if(_menu->getLevel())
        {
            //check the theme
            if(_menu->getTheme()==0){
                Picture bg(_graphicLibrary->getImage(0), 0,_yBackground,MODEL_WIDTH,MODEL_HEIGHT); //background one picture
                Picture bg2(_graphicLibrary->getImage(0), 0,_yBackground2,MODEL_WIDTH,MODEL_HEIGHT); //background two picture

                _window->Draw(bg.getSprite());
                _window->Draw(bg2.getSprite());
            }
            else if(_menu->getTheme()==1){
                Picture bg(_graphicLibrary->getImage(33), 0,_yBackground,SCREEN_WIDTH,MODEL_HEIGHT);
                Picture bg2(_graphicLibrary->getImage(33), 0,_yBackground2,SCREEN_WIDTH,MODEL_HEIGHT);

                _window->Draw(bg.getSprite());
                _window->Draw(bg2.getSprite());
            }

            //before to start the level
            if(_menu->getReady()){
                int tmp = (int)time.GetElapsedTime(); //get the time
                if(tmp%2 == 0){
                    Picture getReady(_graphicLibrary->getImage(7), MODEL_WIDTH/2-50,MODEL_HEIGHT/2-100, 203, 20, 0, 0, 196/2, 13); //get ready picture one
                    _window->Draw(getReady.getSprite());
                }
                else{
                    Picture getReady(_graphicLibrary->getImage(7), MODEL_WIDTH/2-50,MODEL_HEIGHT/2-100, 203, 20, 196/2, 0, 196, 13); //get ready picture two
                    _window->Draw(getReady.getSprite());
                }

                if(time.GetElapsedTime()<=1){
                    addText("3", MODEL_WIDTH/2-7, MODEL_HEIGHT/2-35, 30, col);
                }
                else if(time.GetElapsedTime()<=2){
                    addText("2", MODEL_WIDTH/2-7, MODEL_HEIGHT/2-35, 30, col);
                }
                else if(time.GetElapsedTime()<=3){
                    addText("1", MODEL_WIDTH/2-7, MODEL_HEIGHT/2-35, 30, col);
                }
                else if (time.GetElapsedTime()<=4){
                    addText("Go!", MODEL_WIDTH/2-18, MODEL_HEIGHT/2-35, 30, col);
                }
                else{
                    _menu->setReady(false);
                }
            }
            else{ //the level is playing

                //moove the background
                if(_yBackground > MODEL_HEIGHT - 5){
                    _yBackground = -MODEL_HEIGHT + 2;
                }

                if(_yBackground2 > MODEL_HEIGHT - 5){
                    _yBackground2 = -MODEL_HEIGHT + 2;
                }

                float value = 0.8;

                _yBackground += value;
                _yBackground2 += value;

                int k3 = _gameModel->getNumberTour()%3;
                int k2 = _gameModel->getNumberTour()%2;

                //show ennemies
                if(_gameModel->getLevel()->getEnemiesNumber() > 0)
                {
                    for(auto e : _gameModel->getLevel()->getEnemies())
                    {
                        int xe = e->getX();
                        int ye = e->getY();

                        if(e->getType()==1) //tiny picture
                        {
                            if(_menu->getTheme() == 0){
                                Picture en(_graphicLibrary->getImage(10), xe,ye,TINY_PICTURE_WIDTH,TINY_PICTURE_HEIGHT,0+(TINY_PICTURE_WIDTH/3)*k3,0,(TINY_PICTURE_WIDTH/3)+(TINY_PICTURE_WIDTH/3)*k3,TINY_PICTURE_HEIGHT);
                                _window->Draw(en.getSprite());
                            }
                            else if(_menu->getTheme() == 1){
                                Picture en(_graphicLibrary->getImage(27), xe,ye,SECOND_TINY_WIDTH,SECOND_TINY_HEIGHT);
                                _window->Draw(en.getSprite());
                            }
                        }
                        else if(e->getType()==2) //submarine picture
                        {
                            if(_menu->getTheme() == 0){
                                Picture en(_graphicLibrary->getImage(11), xe,ye,SUBMARINE_PICTURE_WIDTH,SUBMARINE_PICTURE_HEIGHT,0+(SUBMARINE_PICTURE_WIDTH/2)*k2,0,(SUBMARINE_PICTURE_WIDTH/2)+(SUBMARINE_PICTURE_WIDTH/2)*k2,SUBMARINE_PICTURE_HEIGHT);
                                _window->Draw(en.getSprite());
                            }
                            else if(_menu->getTheme() == 1){
                                Picture en(_graphicLibrary->getImage(28), xe,ye,SECOND_SUBMARINE_WIDTH,SECOND_SUBMARINE_HEIGHT);
                                _window->Draw(en.getSprite());
                            }

                        }
                        else if(e->getType()==3) //mighty picture
                        {
                            if(_menu->getTheme() == 0){
                                Picture en(_graphicLibrary->getImage(21), xe,ye,MIGHTY_PICTURE_WIDTH,MIGHTY_PICTURE_HEIGHT,0+(MIGHTY_PICTURE_WIDTH/3)*k3,0,(MIGHTY_PICTURE_WIDTH/3)+(MIGHTY_PICTURE_WIDTH/3)*k3,MIGHTY_PICTURE_HEIGHT);
                                _window->Draw(en.getSprite());
                            }

                            else if(_menu->getTheme() == 1){
                                Picture en(_graphicLibrary->getImage(29), xe,ye,SECOND_MIGHTY_WIDTH,SECOND_MIGHTY_HEIGHT);
                                _window->Draw(en.getSprite());
                            }

                        }
                        //ennemies border life
                        if(_menu->getTheme() == 0){
                            addShape(xe, ye-15, xe+e->getWidth(), ye-15, xe+e->getWidth(), ye-10, xe, ye-10, false, true, 1, 1);
                        }

                        else if(_menu->getTheme() == 1){
                            addShape(xe, ye-15, xe+e->getWidth(), ye-15, xe+e->getWidth(), ye-10, xe, ye-10, false, true, 1, 2);
                        }

                        //ennemies life
                        Shape vieEnemy;
                        vieEnemy.AddPoint(xe, ye-15, Color(240, 76, 36), Color(240, 76, 36));

                        if(e->getType() == 1)
                        {
                            vieEnemy.AddPoint(xe + (((float)e->getHealth() / ((float)TINY_LIFE + (_gameModel->getLevel()->getLevelNumber()- 1) * 10)) * (float)e->getWidth()), ye-15, Color(240, 76, 36), Color(240, 76, 36));
                            vieEnemy.AddPoint(xe + (((float)e->getHealth() / ((float)TINY_LIFE + (_gameModel->getLevel()->getLevelNumber()- 1) * 10)) * (float)e->getWidth()), ye-10, Color(240, 76, 36), Color(240, 76, 36));
                        }
                        else if(e->getType() == 2)
                        {
                            vieEnemy.AddPoint(xe + (((float)e->getHealth() / ((float)SUBMARINE_LIFE + (_gameModel->getLevel()->getLevelNumber() - 1) * 10)) * (float)e->getWidth()), ye-15, Color(240, 76, 36), Color(240, 76, 36));
                            vieEnemy.AddPoint(xe + (((float)e->getHealth() / ((float)SUBMARINE_LIFE + (_gameModel->getLevel()->getLevelNumber() - 1) * 10)) * (float)e->getWidth()), ye-10, Color(240, 76, 36), Color(240, 76, 36));
                        }
                        else if(e->getType() == 3)
                        {
                            vieEnemy.AddPoint(xe + (((float)e->getHealth() / ((float)MIGHTY_LIFE + (_gameModel->getLevel()->getLevelNumber() - 1) * 10)) * (float)e->getWidth()), ye-15, Color(240, 76, 36), Color(240, 76, 36));
                            vieEnemy.AddPoint(xe + (((float)e->getHealth() / ((float)MIGHTY_LIFE + (_gameModel->getLevel()->getLevelNumber() - 1) * 10)) * (float)e->getWidth()), ye-10, Color(240, 76, 36), Color(240, 76, 36));
                        }

                        vieEnemy.AddPoint(xe, ye-10, Color(240, 76, 36), Color(240, 76, 36));
                        vieEnemy.EnableFill(true);
                        vieEnemy.EnableOutline(false);

                        _window->Draw(vieEnemy);
                    }
                }

                //show boss
                if(_gameModel->getLevel()->getEnemiesNumber() <= 0)
                {

                    #ifdef __linux__
                    if(_gameModel->getLevel()->getBoss() != nullptr)
                    #else
                    if(_gameModel->getLevel()->getBoss() != 0)
                    #endif
                    {
                        int xb = _gameModel->getLevel()->getBoss()->getX();
                        int yb = _gameModel->getLevel()->getBoss()->getY();

                        //boss picture
                        if(_menu->getTheme() == 0){
                             Picture b(_graphicLibrary->getImage(1), xb,yb,BOSS_PICTURE_WIDTH, BOSS_PICTURE_HEIGHT, 0+(BOSS_PICTURE_WIDTH/3)*k3,0,(BOSS_PICTURE_WIDTH/3)+(BOSS_PICTURE_WIDTH/3)*k3,BOSS_PICTURE_HEIGHT);
                            _window->Draw(b.getSprite());

                            //boss border life
                        addShape(xb, yb-15,xb+_gameModel->getLevel()->getBoss()->getWidth(), yb-15, xb+_gameModel->getLevel()->getBoss()->getWidth(), yb-10, xb, yb-10, false, true, 1, 1);

                        }

                        else if(_menu->getTheme() == 1){
                             Picture b(_graphicLibrary->getImage(35), xb,yb,BOSS_PICTURE_WIDTH/3, BOSS_PICTURE_HEIGHT);
                            _window->Draw(b.getSprite());

                            addShape(xb, yb-15,xb+_gameModel->getLevel()->getBoss()->getWidth(), yb-15, xb+_gameModel->getLevel()->getBoss()->getWidth(), yb-10, xb, yb-10, false, true, 1, 2);

                        }
                        addShape(xb, yb-15, xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / ((float)BOSS_LIFE + (_gameModel->getLevel()->getLevelNumber()-1) *50)) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb-15, xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / ((float)BOSS_LIFE + (_gameModel->getLevel()->getLevelNumber()-1) *50)) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb-10, xb, yb-10, true, false, 0, 4);

                    }
                }

                //show bullets
                if(_gameModel->getLevel()->getNumberOfBullets() > 0)
                {
                    for(auto b : _gameModel->getLevel()->getBullets())
                    {
                        int xba = b->getX();
                        int yba = b->getY();

                        if(b->getType() == 0)
                        {
                            Picture bba(_graphicLibrary->getImage(12), xba,yba,b->getWidth(),b->getHeight()); //standard ball picture
                            _window->Draw(bba.getSprite());
                        }
                        else if(b->getType() == 1)
                        {
                            Picture bba(_graphicLibrary->getImage(5), xba,yba,b->getWidth(),b->getHeight()); //fireball picture
                            _window->Draw(bba.getSprite());

                        }
                        else if(b->getType() == 2)
                        {
                            Picture bba(_graphicLibrary->getImage(18), xba,yba,b->getWidth(),b->getHeight()); //tiny lase picture
                            _window->Draw(bba.getSprite());

                        }
                        else if(b->getType() == 3)
                        {
                            Picture bba(_graphicLibrary->getImage(23), xba,yba,b->getWidth(),b->getHeight()); //double laser picture
                            _window->Draw(bba.getSprite());
                        }
                        else if(b->getType() == 4)
                        {
                            Picture bba(_graphicLibrary->getImage(4), xba,yba,b->getWidth(),b->getHeight()); //big laser^picture
                            _window->Draw(bba.getSprite());
                        }
                    }
                }
            }

            //show ally
            #ifdef __linux__
            if(_gameModel->getLevel()->getAlly() != nullptr){
            #else
            if(_gameModel->getLevel()->getAlly() != 0){
            #endif
                int xp = _gameModel->getLevel()->getAlly()->getX();
                int yp = _gameModel->getLevel()->getAlly()->getY();
                int w = _gameModel->getLevel()->getAlly()->getWidth();
                int h = _gameModel->getLevel()->getAlly()->getHeight();

                //ally picture
                if(_menu->getTheme() == 0){
                    Picture ally(_graphicLibrary->getImage(17), xp,yp,ALLY_PICTURE_WIDTH,ALLY_PICTURE_HEIGHT,w*(_gameModel->getNumberTour()%3),0,w+w*(_gameModel->getNumberTour()%3),h);
                    _window->Draw(ally.getSprite());

                    //get number of life
                    addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberOfLife(), 50, 5, 15, "x", 40, 5, 15, 0);

                    addShape(100, 10, 200, 10, 200, 20, 100, 20, false, true, 2, 1);
                    addShape(MODEL_WIDTH, 0, SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, MODEL_WIDTH, SCREEN_HEIGHT, true, false, 0, 2);


                }
                else if(_menu->getTheme() == 1){
                    int w = _gameModel->getLevel()->getAlly()->getWidth();
                    int h = _gameModel->getLevel()->getAlly()->getHeight();
                    if(input.IsKeyDown(Key::Right)){
                        Picture ally(_graphicLibrary->getImage(30), xp,yp,SECOND_ALLY_WIDTH,SECOND_ALLY_HEIGHT,0,0,w,h);
                        _window->Draw(ally.getSprite());
                    }
                    else if (input.IsKeyDown(Key::Left)){
                        Picture ally(_graphicLibrary->getImage(30), xp,yp,SECOND_ALLY_WIDTH,SECOND_ALLY_HEIGHT,0,h,w,2*h);
                        _window->Draw(ally.getSprite());
                    }
                    else{
                        Picture ally(_graphicLibrary->getImage(30), xp,yp,SECOND_ALLY_WIDTH,SECOND_ALLY_HEIGHT,0,2*h,w,3*h);
                        _window->Draw(ally.getSprite());
                    }

                    addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberOfLife(), 50, 5, 15, "x", 40, 5, 15, 1);

                    addShape(100, 10, 200, 10, 200, 20, 100, 20, false, true, 2, 0);
                }

                //ally life
                addShape(100, 10, 100 + (((float)_gameModel->getLevel()->getAlly()->getHealth() / (float)ALLY_LIFE) * (float)100), 10, 100 + (((float)_gameModel->getLevel()->getAlly()->getHealth() / (float)ALLY_LIFE) * (float)100), 20, 100, 20, true, false, 0, 4);

                //ally number of life
                Picture life(_graphicLibrary->getImage(25), 15,5,20,20);
                _window->Draw(life.getSprite());

            }

            //show ally main shoot
            if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 0)
            {
                Picture v1(_graphicLibrary->getImage(12), SCREEN_WIDTH-100,170,STANDARD_PICTURE_WIDTH,STANDARD_PICTURE_HEIGHT);
                _window->Draw(v1.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 1)
            {
                Picture v2(_graphicLibrary->getImage(5), SCREEN_WIDTH-100,170,FIREBALL_PICTURE_WIDTH,FIREBALL_PICTURE_HEIGHT);
                _window->Draw(v2.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 2)
            {
                Picture v3(_graphicLibrary->getImage(18), SCREEN_WIDTH-100,170,TINYLASER_PICTURE_WIDTH,TINYLASER_PICTURE_HEIGHT);
                _window->Draw(v3.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 3)
            {
                Picture v4(_graphicLibrary->getImage(23), SCREEN_WIDTH-100,170,LASER_PICTURE_WIDTH,LASER_PICTURE_HEIGHT);
                _window->Draw(v4.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 4)
            {
                Picture v5(_graphicLibrary->getImage(4), SCREEN_WIDTH-100,170,DOUBLE_TINY_LASER_PICTURE_WIDTH,DOUBLE_TINY_LASER_PICTURE_HEIGHT);
                _window->Draw(v5.getSprite());
            }

            //show ally bonus shoot
            if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 0)
            {
                Picture v1(_graphicLibrary->getImage(12), SCREEN_WIDTH-100,305,STANDARD_PICTURE_WIDTH,STANDARD_PICTURE_HEIGHT);
                _window->Draw(v1.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 1)
            {
                Picture v2(_graphicLibrary->getImage(5), SCREEN_WIDTH-100,305,FIREBALL_PICTURE_WIDTH,FIREBALL_PICTURE_HEIGHT);
                _window->Draw(v2.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 2)
            {
                Picture v3(_graphicLibrary->getImage(18), SCREEN_WIDTH-100,305,TINYLASER_PICTURE_WIDTH,TINYLASER_PICTURE_HEIGHT);
                _window->Draw(v3.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 3)
            {
                Picture v4(_graphicLibrary->getImage(23), SCREEN_WIDTH-100,305,LASER_PICTURE_WIDTH,LASER_PICTURE_HEIGHT);
                _window->Draw(v4.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 4)
            {
                Picture v5(_graphicLibrary->getImage(4), SCREEN_WIDTH-100,305,DOUBLE_TINY_LASER_PICTURE_WIDTH,DOUBLE_TINY_LASER_PICTURE_HEIGHT);
                _window->Draw(v5.getSprite());
            }

            if(_menu->getTheme() == 0){
                sf::Shape Line1 = sf::Shape::Line(MODEL_WIDTH, 0, MODEL_WIDTH, MODEL_HEIGHT , 1, Color(255, 255, 255));
                _window->Draw(Line1);

                for(int i = 0; i<10; i++){
                    if(i%2==0){
                        sf::Shape Line1 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 85, MODEL_WIDTH+20*i+20+10, 85 , 1, Color(255, 255, 255));
                        _window->Draw(Line1);

                        sf::Shape Line2 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 205, MODEL_WIDTH+20*i+20+10, 205 , 1, Color(255, 255, 255));
                        _window->Draw(Line2);

                        sf::Shape Line3 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 355, MODEL_WIDTH+20*i+20+10, 355 , 1, Color(255, 255, 255));
                        _window->Draw(Line3);
                    }
                }
            }
            else if(_menu->getTheme() == 1){
                //information frame
                addShape(MODEL_WIDTH, 0, SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, MODEL_WIDTH, SCREEN_HEIGHT, true, false, 0, 6);

                sf::Shape Line1 = sf::Shape::Line(MODEL_WIDTH, 0, MODEL_WIDTH, MODEL_HEIGHT , 1, Color(0, 0, 0));
                _window->Draw(Line1);

                for(int i = 0; i<10; i++){
                    if(i%2==0){
                        sf::Shape Line1 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 85, MODEL_WIDTH+20*i+20+10, 85 , 1, Color(0, 0, 0));
                        _window->Draw(Line1);

                        sf::Shape Line2 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 205, MODEL_WIDTH+20*i+20+10, 205 , 1, Color(0, 0, 0));
                        _window->Draw(Line2);

                        sf::Shape Line3 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 355, MODEL_WIDTH+20*i+20+10, 355 , 1, Color(0, 0, 0));
                        _window->Draw(Line3);
                    }
                }
            }

            //show informations about the level
            if(_menu->getLanguage() == "english"){
                addTextWithValue(_gameModel->getLevel()->getAlly()->getScore(), SCREEN_WIDTH-70, 5, 15, "SCORE :", SCREEN_WIDTH-180, 5, 15, col);
                addTextWithValue(_gameModel->getLevel()->getLevelNumber(), SCREEN_WIDTH - 70, 25, 15, "WAVE :", SCREEN_WIDTH-180, 25, 15, col);
                addTextWithValue(_gameModel->getLevel()->getNumberOfEnemies(), SCREEN_WIDTH - 70, 45, 15, "ENEMIES : ", SCREEN_WIDTH - 180, 45, 15, col);

                addText("MAIN SHOOT", SCREEN_WIDTH - 135, 100, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getOneBulletBonus(_gameModel->getLevel()->getAlly()->getMainBulletType())->getDamage(), SCREEN_WIDTH - 70, 130, 15, "POWER : ", SCREEN_WIDTH - 180, 130, 15, col);


                addText("BONUS SHOOT", SCREEN_WIDTH-135, 220, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getBulletBonus()->getDamage(), SCREEN_WIDTH - 70, 245, 15, "POWER :", SCREEN_WIDTH - 180, 245, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberShootBonusMax()-_gameModel->getLevel()->getAlly()->getNumberShootBonus(), SCREEN_WIDTH - 70, 265, 15, "NUMBER :", SCREEN_WIDTH - 180, 265, 15, col);
            }
            else if (_menu->getLanguage() == "francais"){
                addTextWithValue(_gameModel->getLevel()->getAlly()->getScore(), SCREEN_WIDTH-70, 5, 15, "SCORE :", SCREEN_WIDTH-180, 5, 15, col);
                addTextWithValue(_gameModel->getLevel()->getLevelNumber(), SCREEN_WIDTH - 70, 25, 15, "VAGUE :", SCREEN_WIDTH-180, 25, 15, col);
                addTextWithValue(_gameModel->getLevel()->getNumberOfEnemies(), SCREEN_WIDTH - 70, 45, 15, "ENNEMIES : ", SCREEN_WIDTH - 180, 45, 15, col);

                addText("TIR PRINCIPAL", SCREEN_WIDTH - 150, 100, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getOneBulletBonus(_gameModel->getLevel()->getAlly()->getMainBulletType())->getDamage(), SCREEN_WIDTH - 70, 130, 15, "PUISSANCE : ", SCREEN_WIDTH - 180, 130, 15, col);


                addText("TIR BONUS", SCREEN_WIDTH-135, 220, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getBulletBonus()->getDamage(), SCREEN_WIDTH - 70, 245, 15, "PUISSANCE :", SCREEN_WIDTH - 180, 245, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberShootBonusMax()-_gameModel->getLevel()->getAlly()->getNumberShootBonus(), SCREEN_WIDTH - 70, 265, 15, "NOMBRE :", SCREEN_WIDTH - 180, 265, 15, col);
            }
            else if(_menu->getLanguage() == "deutsch"){
                addTextWithValue(_gameModel->getLevel()->getAlly()->getScore(), SCREEN_WIDTH-70, 5, 15, "ERGEBNIS :", SCREEN_WIDTH-180, 5, 15, col);
                addTextWithValue(_gameModel->getLevel()->getLevelNumber(), SCREEN_WIDTH - 70, 25, 15, "XELLE :", SCREEN_WIDTH-180, 25, 15, col);
                addTextWithValue(_gameModel->getLevel()->getNumberOfEnemies(), SCREEN_WIDTH - 70, 45, 15, "FEIND : ", SCREEN_WIDTH - 180, 45, 15, col);

                addText("HAUPT BRENNEN", SCREEN_WIDTH - 155, 100, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getOneBulletBonus(_gameModel->getLevel()->getAlly()->getMainBulletType())->getDamage(), SCREEN_WIDTH - 70, 130, 15, "LEISTUNG : ", SCREEN_WIDTH - 180, 130, 15, col);


                addText("BONUS BRENNEN", SCREEN_WIDTH-155, 220, 15,col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getBulletBonus()->getDamage(), SCREEN_WIDTH - 70, 245, 15, "LEISTUNG :", SCREEN_WIDTH - 180, 245, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberShootBonusMax()-_gameModel->getLevel()->getAlly()->getNumberShootBonus(), SCREEN_WIDTH - 70, 265, 15, "ANZAHL :", SCREEN_WIDTH - 180, 265, 15, col);
            }
        }



        if(_menu->getShop())
        {
            //show line to delimit items
            if(_menu->getTheme() == 0){
                Picture bg(_graphicLibrary->getImage(26), 0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
                _window->Draw(bg.getSprite());

                sf::Shape Line0 = sf::Shape::Line(150, 90, 150, 100*6+90 , 1, Color(255, 255, 255));
                _window->Draw(Line0);

                sf::Shape Line1 = sf::Shape::Line(10, 100*1+90, SCREEN_WIDTH-10, 100*1+90 , 1, Color(255, 255, 255));
                _window->Draw(Line1);

                sf::Shape Line2 = sf::Shape::Line(10, 100*2+90, SCREEN_WIDTH-10, 100*2+90 , 1, Color(255, 255, 255));
                _window->Draw(Line2);

                sf::Shape Line3 = sf::Shape::Line(10, 100*3+90, SCREEN_WIDTH-10, 100*3+90 , 1, Color(255, 255, 255));
                _window->Draw(Line3);

                sf::Shape Line4 = sf::Shape::Line(10, 100*4+90, SCREEN_WIDTH-10, 100*4+90 , 1, Color(255, 255, 255));
                _window->Draw(Line4);

                sf::Shape Line5 = sf::Shape::Line(10, 100*5+90, SCREEN_WIDTH-10, 100*5+90 , 1, Color(255, 255, 255));
                _window->Draw(Line5);

                addShape(450, 610, 550, 610, 550, 630, 450, 630, false, true, 1, 1);

                addShape(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-75, SCREEN_HEIGHT-20, false, true, 2, 1);

                if((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20))
                {
                    addShape(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-75, SCREEN_HEIGHT-20, true, false, 0, 3);
                }
            }
            else if(_menu->getTheme() == 1){
                _window->Clear(Color(180, 80, 253));

                sf::Shape Line0 = sf::Shape::Line(150, 90, 150, 100*6+90 , 1, Color(0, 0, 0));
                _window->Draw(Line0);

                sf::Shape Line1 = sf::Shape::Line(10, 100*1+90, SCREEN_WIDTH-10, 100*1+90 , 1, Color(0, 0, 0));
                _window->Draw(Line1);

                sf::Shape Line2 = sf::Shape::Line(10, 100*2+90, SCREEN_WIDTH-10, 100*2+90 , 1, Color(0, 0, 0));
                _window->Draw(Line2);

                sf::Shape Line3 = sf::Shape::Line(10, 100*3+90, SCREEN_WIDTH-10, 100*3+90 , 1, Color(0, 0, 0));
                _window->Draw(Line3);

                sf::Shape Line4 = sf::Shape::Line(10, 100*4+90, SCREEN_WIDTH-10, 100*4+90 , 1, Color(0, 0, 0));
                _window->Draw(Line4);

                sf::Shape Line5 = sf::Shape::Line(10, 100*5+90, SCREEN_WIDTH-10, 100*5+90 , 1, Color(0, 0, 0));
                _window->Draw(Line5);

                addShape(450, 610, 550, 610, 550, 630, 450, 630, false, true, 1, 0);

                Picture button(_graphicLibrary->getImage(36), SCREEN_WIDTH/2-75,SCREEN_HEIGHT-50,300, 30, 0,0, 150, 80);
                _window->Draw(button.getSprite());
                if((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)){
                    Picture button(_graphicLibrary->getImage(36), SCREEN_WIDTH/2-75,SCREEN_HEIGHT-50,300, 30, 150,0, 300, 80);
                    _window->Draw(button.getSprite());
                }
            }

            Picture life(_graphicLibrary->getImage(25), 70, 620, 20, 20);
            _window->Draw(life.getSprite());

            if(_menu->getLanguage() == "english"){
                addTextWithValue(_gameModel->getLevel()->getAlly()->getScore(), 115, 30, 15, "Money : ", 15, 30, 15, col);
                int rang = 1;
                showItems(rang, 12, "Standard ball", STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 5, "Fire ball", FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 18, "Little laser", 9, 20, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 4, "Double laser", 17, 16, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 23, "Big laser", 8, 30, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                addText("New life", 25, 660, 15, col);
                addText("Buy", 490, 612, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberOfLife(), 270, 620, 15, "Life :", 175, 620, 15, col);
                addTextWithValue(ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100, 270, 640, 15, "Price :", 175, 640, 15, col);
                addText("NEXT LEVEL", SCREEN_WIDTH/2-60, SCREEN_HEIGHT-45, 20, col);


                if(mouseX>450 && mouseX<550 && mouseY>610 && mouseY<630){
                    addShape(450, 610, 550, 610, 550, 630, 450, 630, true, false, 0, 5);
                    addText("Buy", 490, 612, 15, 1);
                }
            }
            else if (_menu->getLanguage() == "francais"){
                addTextWithValue(_gameModel->getLevel()->getAlly()->getScore(), 115, 30, 15, "Argent : ", 15, 30, 15, col);
                int rang = 1;
                showItems(rang, 12, "Balle standard", STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 5, "Balle de feu", FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 18, "Petit laser", 9, 20, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 4, "Double laser", 17, 16, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 23, "Gros laser", 8, 30, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                addText("Nouvelle vie", 25, 660, 15, col);
                addText("Acheter", 470, 612, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberOfLife(), 270, 620, 15, "Vies :", 175, 620, 15, col);
                addTextWithValue(ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100, 270, 640, 15, "Prix :", 175, 640, 15, col);
                 addText("SUIVANT", SCREEN_WIDTH/2-45, SCREEN_HEIGHT-45, 20, col);

                if(mouseX>450 && mouseX<550 && mouseY>610 && mouseY<630){
                    addShape(450, 610, 550, 610, 550, 630, 450, 630, true, false, 0, 5);
                    addText("Acheter", 470, 612, 15, 1);
                }
            }
            else if(_menu->getLanguage() == "deutsch"){
                addTextWithValue(_gameModel->getLevel()->getAlly()->getScore(), 115, 30, 15, "Gelt : ", 15, 30, 15, col);
                int rang = 1;
                showItems(rang, 12, "Ball standard", STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 5, "Ball feuer", FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 18, "Wenig laser", 9, 20, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 4, "Doppelt laser", 17, 16, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                rang++;
                showItems(rang, 23, "Grob laser", 8, 30, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
                addText("Neues leben", 25, 660, 15, col);
                addText("Kaufen", 470, 612, 15, col);
                addTextWithValue(_gameModel->getLevel()->getAlly()->getNumberOfLife(), 270, 620, 15, "Leben :", 175, 620, 15, col);
                addTextWithValue(ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100, 270, 640, 15, "Preis :", 175, 640, 15, col);
                addText("NACHSTER", SCREEN_WIDTH/2-45, SCREEN_HEIGHT-45, 20, col);

                if(mouseX>450 && mouseX<550 && mouseY>610 && mouseY<630){
                    addShape(450, 610, 550, 610, 550, 630, 450, 630, true, false, 0, 5);
                    addText("Kaufen", 470, 612, 15, 1);
                }
            }
        }
        else if(_menu->getSaveScore()){
            if(_menu->getTheme() == 0){
                _window->Clear(Color(1,67,171));

                addShape(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-75, SCREEN_HEIGHT-20, false, true, 2, 1);
                if(((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
                {
                    addShape(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+75, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-75, SCREEN_HEIGHT-20, true, false, 0, 3);
                }
            }
            else if(_menu->getTheme() == 1){
                _window->Clear(Color(0,0,0));

                Picture button(_graphicLibrary->getImage(36), SCREEN_WIDTH/2-75,SCREEN_HEIGHT-50,300, 30, 0,0, 150, 80);
                _window->Draw(button.getSprite());
                if((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)){
                    Picture button(_graphicLibrary->getImage(36), SCREEN_WIDTH/2-75,SCREEN_HEIGHT-50,300, 30, 150,0, 300, 80);
                    _window->Draw(button.getSprite());
                }
            }

            int tmp = (int)time.GetElapsedTime();
            if(tmp%3 == 0){
                Picture gameOver(_graphicLibrary->getImage(6), SCREEN_WIDTH/2-97,100, 388,26, 0, 0, 97, 13);
                _window->Draw(gameOver.getSprite());
            }
            else{
                Picture gameOver(_graphicLibrary->getImage(6), SCREEN_WIDTH/2-97,100, 388,26, 97, 0, 194, 13);
                _window->Draw(gameOver.getSprite());
            }

            addText(_gameModel->getLevel()->getAlly()->getName(), 280, 270, 20, 0);


            if(tmp%2 == 0){
                unsigned int pos = (int)_gameModel->getLevel()->getAlly()->getName().size();
                addText("|", 280+11.5*pos, 270, 20, 0);
            }

            addTextWithValue(_gameModel->getLevel()->getAlly()->getScore(), 250, 300, 20, "Score :", 150, 300, 20, 0);

            if(_menu->getLanguage() == "english"){
                addText("Your name :", 150, 270, 20, 0);
                addText("Confirm", SCREEN_WIDTH/2-60, SCREEN_HEIGHT-45, 20, 0);
            }
            else if(_menu->getLanguage() == "francais"){
                addText("Votre nom :", 150, 270, 20, 0);
                addText("Confirmer", SCREEN_WIDTH/2-55, SCREEN_HEIGHT-45, 20, 0);
            }
            else if(_menu->getLanguage() == "deutsch"){
                addText("Ihren namen :", 140, 270, 20, 0);
                addText("Bestatigen", SCREEN_WIDTH/2-55, SCREEN_HEIGHT-45, 20, 0);
            }
        }
    }

    else if(_menu->getScore()){

        addShape(SCREEN_WIDTH/2-90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-90, SCREEN_HEIGHT-20, false, true, 2, 1);
        if(((mouseX > SCREEN_WIDTH/2-90) && (mouseX < SCREEN_WIDTH/2+90) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
        {
            addShape(SCREEN_WIDTH/2-90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-90, SCREEN_HEIGHT-20, true, false, 0, 4);
        }
        if(_menu->getLanguage() == "english"){
            addText("BACK TO MENU", SCREEN_WIDTH/2-70, SCREEN_HEIGHT-45, 20, 0);
        }
        else if (_menu->getLanguage() == "francais"){
            addText("RETOUR AU MENU", SCREEN_WIDTH/2-80, SCREEN_HEIGHT-45, 20, 0);
        }
        else if (_menu->getLanguage() == "deutsch"){
            addText("ZURUCK ZUM MENU", SCREEN_WIDTH/2-85, SCREEN_HEIGHT-45, 20, 0);
        }


        int tmp = (int)time.GetElapsedTime();
        if(tmp%2 == 0){
            Picture hightScore(_graphicLibrary->getImage(24), SCREEN_WIDTH/2-114,10, 456,26, 0, 0, 114, 13);
            _window->Draw(hightScore.getSprite());
        }
        else{
            Picture hightScore(_graphicLibrary->getImage(24), SCREEN_WIDTH/2+114,10, 456,26, 228, 0, 114, 13);
            _window->Draw(hightScore.getSprite());
        }

        if(_menu->showScores(YOUR_FILE).size()>0)
        {
            std::vector<Player*> players = _menu->showScores(YOUR_FILE);
            for(int i = 0; i<10 ; i++)
            {
                if(i<players.size()){
                    addTextWithValue(i+1, 100, 40*i+100, 15, ")", 120, 40*i+100, 15, 0);
                    addTextWithValue(players[i]->getScore(), 400, 40*i+100, 15, players[i]->getName(), 145, 40*i+100, 15, 0);
                }
            }
        }
        else
        {
            addText("The file is emplty !", SCREEN_WIDTH/2-70, 140, 15, 0);
        }
    }
    else if(_menu->getOptions()){
        Picture credits(_graphicLibrary->getImage(20), SCREEN_WIDTH/2-73,15,146,26);
        _window->Draw(credits.getSprite());

        addShape(280, 160, 290, 160, 290, 170, 280, 170, true, false, 0, 4);
        addShape(280, 160, 290, 160, 290, 170, 280, 170, false, true, 1, 1);

        addShape(280, 140, 290, 140, 290, 150, 280, 150, true, false, 0, 4);
        addShape(280, 140, 290, 140, 290, 150, 280, 150, false, true, 1, 1);

        addShape(280, 180, 290, 180, 290, 190, 280, 190, true, false, 0, 4);
        addShape(280, 180, 290, 180, 290, 190, 280, 190, false, true, 1, 1);



        switch(_menu->getTheme()){
        case 0:
            addShape(180, 250, 350, 250, 350, 310, 180, 310, false, true, 4, 3);
            addShape(180, 340, 280, 340, 280, 430, 180, 430, false, true, 4, 4);
            break;
        case 1:
            addShape(180, 250, 350, 250, 350, 310, 180, 310, false, true, 4, 4);
            addShape(180, 340, 280, 340, 280, 430, 180, 430, false, true, 4, 3);
            break;
        }

        if(mouseX> 180 && mouseX<350 && mouseY>250 && mouseY<310){
            addShape(180, 250, 350, 250, 350, 310, 180, 310, false, true, 4, 5);
        }
        if(mouseX> 180 && mouseX<280 && mouseY>340 && mouseY<430){
            addShape(180, 340, 280, 340, 280, 430, 180, 430, false, true, 4, 5);
        }
        Picture theme1(_graphicLibrary->getImage(22), 180,250,170,60);
        _window->Draw(theme1.getSprite());

        Picture theme2(_graphicLibrary->getImage(32), 180,340,100,90);
        _window->Draw(theme2.getSprite());


        addShape(SCREEN_WIDTH/2-90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-90, SCREEN_HEIGHT-20, false, true, 2, 1);



        if(((mouseX > SCREEN_WIDTH/2-90) && (mouseX < SCREEN_WIDTH/2+90) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
        {
            addShape(SCREEN_WIDTH/2-90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-90, SCREEN_HEIGHT-20, true, false, 0, 4);
        }

        if(_menu->getLanguage() == "english"){
            addShape(280, 140, 290, 140, 290, 150, 280, 150, true, false, 0, 3);

            addText("Langage : ", 100, 135, 15, 0);
            addText("English", 180, 135, 15, 0);
            addText("French", 180, 155, 15, 0);
            addText("Dutch", 180, 175, 15, 0);

            addText("Theme : ", 100, 250, 15, 0);

            addText("Difficulty : ", 100, 500, 15, 0);

            addText("BACK TO MENU", SCREEN_WIDTH/2-70, SCREEN_HEIGHT-45, 20, 0);
        }
        else if (_menu->getLanguage() == "francais"){
            addShape(280, 160, 290, 160, 290, 170, 280, 170, true, false, 0, 3);

            addText("Langue : ", 100, 135, 15, 0);
            addText("Anglais", 180, 135, 15, 0);
            addText("Francais", 180, 155, 15, 0);
            addText("Allemand", 180, 175, 15, 0);

            addText("Theme : ", 100, 250, 15, 0);

            addText("Difficulte : ", 100, 500, 15, 0);

            addText("RETOUR AU MENU", SCREEN_WIDTH/2-80, SCREEN_HEIGHT-45, 20, 0);
        }
        else if (_menu->getLanguage() == "deutsch"){
            addShape(280, 180, 290, 180, 290, 190, 280, 190, true, false, 0, 3);

            addText("Sprache : ", 100, 135, 15, 0);
            addText("Englisch", 180, 135, 15, 0);
            addText("Franzosisch", 180, 155, 15, 0);
            addText("Deutsch", 180, 175, 15, 0);

            addText("Thema : ", 100, 250, 15, 0);

            addText("Schwierigkeit : ", 100, 500, 15, 0);

            addText("ZURUCK ZUM MENU", SCREEN_WIDTH/2-85, SCREEN_HEIGHT-45, 20, 0);
        }

        addShape(250, 500, 270, 500, 270, 520, 250, 520, false, true, 2, 1);
        addShape(420, 500, 440, 500, 440, 520, 420, 520, false, true, 2, 1);

        if(mouseY>500 && mouseY<520){
            if(mouseX>250 && mouseX<270){
                if(_gameModel->getDifficulty()>0)
                    addShape(250, 500, 270, 500, 270, 520, 250, 520, true, false, 0, 3);
                else
                    addShape(250, 500, 270, 500, 270, 520, 250, 520, true, false, 0, 4);
            }
            if(mouseX>420 && mouseX<440){
                if(_gameModel->getDifficulty()<10)
                    addShape(420, 500, 440, 500, 440, 520, 420, 520, true, false, 0, 3);
                else
                    addShape(420, 500, 440, 500, 440, 520, 420, 520, true, false, 0, 4);
            }
        }

        addText("-", 252, 495, 25, 0);
        addText("+", 422, 495, 25, 0);
        for(int i = 0 ; i < 10; i++){
            if(i<_gameModel->getDifficulty()){
                addShape(250+20*i, 530, 260+20*i, 530, 260+20*i, 540, 250+20*i, 540, true, false, 0, 4);
            }
            addShape(250+20*i, 530, 260+20*i, 530, 260+20*i, 540, 250+20*i, 540, false, true, 1, 1);
        }

        if(mouseX>280 && mouseX<290){
            if(mouseY>160 && mouseY<170){
                addShape(280, 160, 290, 160, 290, 170, 280, 170, true, false, 0, 5);
            }
            else if (mouseY>140 && mouseY<150){
                addShape(280, 140, 290, 140, 290, 150, 280, 150, true, false, 0, 5);
            }
            else if (mouseY>180 && mouseY<190){
                addShape(280, 180, 290, 180, 290, 190, 280, 190, true, false, 0, 5);
            }
        }
    }
    else if (_menu->getCredits()){
        Picture credits(_graphicLibrary->getImage(2), SCREEN_WIDTH/2-73,15,146,26);
        _window->Draw(credits.getSprite());

        Picture logo(_graphicLibrary->getImage(34), SCREEN_WIDTH/2-90,320,180,120);
        _window->Draw(logo.getSprite());

        addText("(ari [arobas] arifeldman.com)", 15, 120, 15, 2);

        if(_menu->getLanguage() == "english"){
            addText("Game artwork created by Ari Feldman (theme 1),", 15, 100, 15, 0);
            addText("and Romain Bourqui (theme 2).", 15, 140, 15, 0);
            addText("Thank you to our teacher Olivier Guibert and Franck Ruby", 15, 180, 15, 0);
            addText("for the conception and programming help.", 15, 200, 15, 0);
            addText("Game designed by Maxime Maheo and Nicolas Valaise,", 15, 260, 15, 0);
            addText("informatique IUT of Bordeaux.", 15, 280, 15, 0);
            addText("Original game : Shoot Them Up", 15, 480, 15, 0);

            addShape(SCREEN_WIDTH/2-85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-85, SCREEN_HEIGHT-20, false, true, 2, 1);

            if(((mouseX > SCREEN_WIDTH/2-85) && (mouseX < SCREEN_WIDTH/2+85) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
            {
                addShape(SCREEN_WIDTH/2-85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-85, SCREEN_HEIGHT-20, true, false, 0, 4);
            }
            addText("BACK TO MENU", SCREEN_WIDTH/2-70, SCREEN_HEIGHT-45, 20, 0);

        }
        else if (_menu->getLanguage() == "francais"){
            addText("Les images du jeu ont ete cree par Ari Feldman (theme 1),", 15, 100, 15, 0);
            addText("et Romain Bourqui (theme 2).", 15, 140, 15, 0);
            addText("Merci a nos professeurs Olivier Guibert et Franck Ruby", 15, 180, 15, 0);
            addText("pour l'aide sur la conception et la programmation.", 15, 200, 15, 0);
            addText("Jeu cree par Maxime Maheo et Nicolas Valaise,", 15, 260, 15, 0);
            addText("etudiant a l'IUT Informatique de Bordeaux.", 15, 280, 15, 0);
            addText("Jeu original : Shoot Them Up", 15, 480, 15, 0);

            addShape(SCREEN_WIDTH/2-85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-85, SCREEN_HEIGHT-20, false, true, 2, 1);

            if(((mouseX > SCREEN_WIDTH/2-85) && (mouseX < SCREEN_WIDTH/2+85) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
            {
                addShape(SCREEN_WIDTH/2-85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+85, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-85, SCREEN_HEIGHT-20, true, false, 0, 4);
            }

            addText("RETOUR AU MENU", SCREEN_WIDTH/2-80, SCREEN_HEIGHT-45, 20, 0);
        }
        else if (_menu->getLanguage() == "deutsch"){
            addText("Bilder des spiels wurden erstellt par Ari Feldman (thema 1),", 15, 100, 15, 0);
            addText("und Romain Bourqui (thema 2).", 15, 140, 15, 0);
            addText("Wir danken Ihnen, unseren lehrern Olivier Guibert und Franck Ruby", 15, 180, 15, 0);
            addText("hilfe auf die Gestaltung und Programmierung.", 15, 200, 15, 0);
            addText("Spiel erstellt Maxime Maheo und Nicolas Valaise,", 15, 260, 15, 0);
            addText("studie a l'IUT datenverarbeitung de Bordeaux.", 15, 280, 15, 0);
            addText("Original-Spiel : Shoot Them Up", 15, 480, 15, 0);


            addShape(SCREEN_WIDTH/2-90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-90, SCREEN_HEIGHT-20, false, true, 2, 1);
            if(((mouseX > SCREEN_WIDTH/2-90) && (mouseX < SCREEN_WIDTH/2+90) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
            {
                addShape(SCREEN_WIDTH/2-90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-50, SCREEN_WIDTH/2+90, SCREEN_HEIGHT-20, SCREEN_WIDTH/2-90, SCREEN_HEIGHT-20, true, false, 0, 4);
            }

            addText("ZURUCK ZUM MENU", SCREEN_WIDTH/2-85, SCREEN_HEIGHT-45, 20, 0);
        }
    }
    else if(_menu->getEnding())
    {

    }
    _window->Display();
}

void GameViewSFML::showItems(int rang, int numPicture, string name, int width, int height, int price, int damage) const{
    const Input& input = _window->GetInput();
    int mouseX = input.GetMouseX();
    int mouseY = input.GetMouseY();

    Picture item(_graphicLibrary->getImage((numPicture)), 60, 30+rang*100, width, height);
    _window->Draw(item.getSprite());

    addText(name, 25, 100*rang+60, 15, _menu->getTheme());

    addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, false, true, 1, _menu->getTheme()+1);
    addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, false, true, 1, _menu->getTheme()+1);

    if(_menu->getLanguage() == "english"){
        addTextWithValue(price, 270, 100*rang+40, 15, "Price : ", 175, 100*rang+40, 15, _menu->getTheme());
        addTextWithValue(damage, 270, 100*rang+60, 15, "Damages : ", 175, 100*rang+60, 15, _menu->getTheme());
        addText("State : ", 175, 100*rang+20, 15, _menu->getTheme());
        addText("Improve", 470, 100*rang+13, 15, _menu->getTheme());
        addText("Arm", 485, 100*rang+52, 15, _menu->getTheme());
        if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getType()){
            addText("(bonus shoot)", 248, 100*rang, 15, _menu->getTheme());
        }


        if(mouseX > 450 && mouseX < 550 && mouseY>100*rang+10 && mouseY<100*rang+30){
            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang-1)){
                addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, true, false, 0, 3);
            }
            else{
                addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, true, false, 0, 6);
            }
            addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, false, true, 1, 2);
            addText("Improve", 470, 100*rang+13, 15, 1);

        }
        if(mouseX > 450 && mouseX < 550 && mouseY>100*rang+50 && mouseY<100*rang+70){
            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang-1)){
             addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, true, false, 0, 3);
            }
            else{
                addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, true, false, 0, 6);
            }
            addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, false, true, 1, 2);
            addText("Arm", 485, 100*rang+52, 15, 1);
        }

    }
    else if (_menu->getLanguage() == "francais"){
        addTextWithValue(price, 270, 100*rang+40, 15, "Prix : ", 175, 100*rang+40, 15, _menu->getTheme());
        addTextWithValue(damage, 270, 100*rang+60, 15, "Dommages : ", 175, 100*rang+60, 15, _menu->getTheme());
        addText("Etat : ", 175, 100*rang+20, 15, _menu->getTheme());
        addText("Ameliorer", 462, 100*rang+13, 15, _menu->getTheme());
        addText("Armer", 480, 100*rang+52, 15, _menu->getTheme());
        if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getType()){
            addText("(tir bonus)", 248, 100*rang, 15, _menu->getTheme());
        }

        if(mouseX > 450 && mouseX < 550 && mouseY>100*rang+10 && mouseY<100*rang+30){
            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang-1)){
                addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, true, false, 0, 3);
            }
            else{
                addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, true, false, 0, 6);
            }
            addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, false, true, 1, 2);
            addText("Ameliorer", 462, 100*rang+13, 15, 1);
        }
        if(mouseX > 450 && mouseX < 550 && mouseY>100*rang+50 && mouseY<100*rang+70){
            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang-1)){
                addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, true, false, 0, 3);
            }
            else{
                addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, true, false, 0, 6);
            }
            addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, false, true, 1, 2);
            addText("Armer", 480, 100*rang+52, 15, 1);
        }

    }
    else if (_menu->getLanguage() == "deutsch"){
        addTextWithValue(price, 270, 100*rang+40, 15, "Preis : ", 175, 100*rang+40, 15, _menu->getTheme());
        addTextWithValue(damage, 270, 100*rang+60, 15, "Schaden : ", 175, 100*rang+60, 15, _menu->getTheme());
        addText("Zustand : ", 175, 100*rang+20, 15, _menu->getTheme());
        addText("Verbessern", 455, 100*rang+13, 15, _menu->getTheme());
        addText("Arm", 490, 100*rang+52, 15, _menu->getTheme());
        if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getType()){
            addText("(bonus brennen)", 243, 100*rang, 15, _menu->getTheme());
        }

        if(mouseX > 450 && mouseX < 550 && mouseY>100*rang+10 && mouseY<100*rang+30){
            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang-1)){
                addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, true, false, 0, 3);
            }
            else{
                addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, true, false, 0, 6);
            }
            addShape(450, 100*rang+10, 550, 100*rang+10, 550, 100*rang+30, 450, 100*rang+30, false, true, 1, 2);
            addText("Verbessern", 455, 100*rang+13, 15, 1);
        }
        if(mouseX > 450 && mouseX < 550 && mouseY>100*rang+50 && mouseY<100*rang+70){
            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang-1)){
                addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, true, false, 0, 3);
            }
            else{
                addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, true, false, 0, 6);
            }
            addShape(450, 100*rang+50, 550, 100*rang+50, 550, 100*rang+70, 450, 100*rang+70, false, true, 1, 2);
            addText("Arm", 490, 100*rang+52, 15, 1);
        }

    }

    for(int i = 0; i<5; i++){
        addShape(250+25*i, rang*100+25, 260+25*i, rang*100+25, 260+25*i, rang*100+35, 250+25*i, rang*100+35, false, true, 1, 1);


        if(_gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getState()>i){
            addShape(250+25*i, rang*100+25, 260+25*i, rang*100+25, 260+25*i, rang*100+35, 250+25*i, rang*100+35, true, false, 1, 3);

        }
        else{
            addShape(250+25*i, rang*100+25, 260+25*i, rang*100+25, 260+25*i, rang*100+35, 250+25*i, rang*100+35, true, false, 1, 4);
        }
    }
}


void GameViewSFML::addText(std::string text, int x, int y, int size, int color) const{
    String newText(text, font , size);
    newText.SetX(x);
    newText.SetY(y);
    Color c;

    switch (color) {
        case 0:
            c = Color::White;
            break;
        case 1:
            c = Color::Black;
            break;
        case 2:
            c = Color::Red;
            break;
    }

    newText.SetColor(c);
    _window->Draw(newText);
}

void GameViewSFML::addTextWithValue(int value, int xV, int yV, int sizeV, std::string text, int xT, int yT, int sizeT, int color) const{
    Color c;
    switch (color) {
        case 0:
            c = Color::White;
            break;
        case 1:
            c = Color::Black;
            break;
    }

    String newText(text, font , sizeT);
    newText.SetX(xT);
    newText.SetY(yT);
    newText.SetColor(c);
    _window->Draw(newText);

    std::string newValue;
    std::stringstream out;
    out << value;
    newValue = out.str();

    String textValue(newValue, font , sizeV);
    textValue.SetX(xV);
    textValue.SetY(yV);
    textValue.SetColor(c);
    _window->Draw(textValue);
}

void GameViewSFML::addShape(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool fill, bool outLine, int width, int color) const{
    Color c;
    switch (color) {
        case 1:
            c = Color::White;
            break;
        case 2:
            c = Color::Black;
            break;
        case 3:
            c = Color::Green;
            break;
        case 4:
            c = Color::Red;
            break;
        case 5:
            c = Color::Yellow;
            break;
        case 6:
            c = Color(255, 153, 51);
            break;
        default:
            break;
    }

    Shape s;
    s.AddPoint(x1, y1, c, c);
    s.AddPoint(x2, y2, c, c);
    s.AddPoint(x3, y3, c, c);
    s.AddPoint(x4, y4, c, c);
    s.EnableFill(fill);
    s.EnableOutline(outLine);
    s.SetOutlineWidth(width);

    _window->Draw(s);
}

bool GameViewSFML::treatEvent(){

    bool result = true;
    const Input& input = _window->GetInput();

    int mouseX = input.GetMouseX();
    int mouseY = input.GetMouseY();

    if (_window->IsOpened())
    {
        Event Event;
        while (_window->GetEvent(Event))
        {
            // Fenêtre fermée
            if (Event.Type == Event::Closed){
                _window->Close();
                result = false;
            }

            // Touche 'echap' appuyée
            if ((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Escape)){
                _window->Close();
                result = false;
            }
            if(Event.Type == Event::MouseButtonReleased){
                _mouseClicked = false;
            }
            if (_menu->getSaveScore()){
                if(Event.Type == Event::KeyReleased){
                    _letterPut = true;
                }
                if(Event.Type == Event::KeyPressed && _letterPut){
                    switch (Event.Key.Code) {
                        case Key::A:
                            _gameModel->getLevel()->getAlly()->addLetter("a");
                            _letterPut = false;
                            break;
                        case Key::B:
                            _gameModel->getLevel()->getAlly()->addLetter("b");
                            _letterPut = false;
                            break;
                        case Key::C:
                            _gameModel->getLevel()->getAlly()->addLetter("c");
                            _letterPut = false;
                            break;
                        case Key::D:
                            _gameModel->getLevel()->getAlly()->addLetter("d");
                            _letterPut = false;
                            break;
                        case Key::E:
                            _gameModel->getLevel()->getAlly()->addLetter("e");
                            _letterPut = false;
                            break;
                        case Key::F:
                            _gameModel->getLevel()->getAlly()->addLetter("f");
                            _letterPut = false;
                            break;
                        case Key::G:
                            _gameModel->getLevel()->getAlly()->addLetter("g");
                            _letterPut = false;
                            break;
                        case Key::H:
                            _gameModel->getLevel()->getAlly()->addLetter("h");
                            _letterPut = false;
                            break;
                        case Key::I:
                            _gameModel->getLevel()->getAlly()->addLetter("i");
                            _letterPut = false;
                            break;
                        case Key::J:
                            _gameModel->getLevel()->getAlly()->addLetter("j");
                            _letterPut = false;
                            break;
                        case Key::K:
                            _gameModel->getLevel()->getAlly()->addLetter("k");
                            _letterPut = false;
                            break;
                        case Key::L:
                            _gameModel->getLevel()->getAlly()->addLetter("l");
                            _letterPut = false;
                            break;
                        case Key::M:
                            _gameModel->getLevel()->getAlly()->addLetter("m");
                            _letterPut = false;
                            break;
                        case Key::N:
                            _gameModel->getLevel()->getAlly()->addLetter("n");
                            _letterPut = false;
                            break;
                        case Key::O:
                            _gameModel->getLevel()->getAlly()->addLetter("o");
                            _letterPut = false;
                            break;
                        case Key::P:
                            _gameModel->getLevel()->getAlly()->addLetter("p");
                            _letterPut = false;
                            break;
                        case Key::Q:
                            _gameModel->getLevel()->getAlly()->addLetter("q");
                            _letterPut = false;
                            break;
                        case Key::R:
                            _gameModel->getLevel()->getAlly()->addLetter("r");
                            _letterPut = false;
                            break;
                        case Key::S:
                            _gameModel->getLevel()->getAlly()->addLetter("s");
                            _letterPut = false;
                            break;
                        case Key::T:
                            _gameModel->getLevel()->getAlly()->addLetter("t");
                            _letterPut = false;
                            break;
                        case Key::U:
                            _gameModel->getLevel()->getAlly()->addLetter("u");
                            _letterPut = false;
                            break;
                        case Key::V:
                            _gameModel->getLevel()->getAlly()->addLetter("v");
                            _letterPut = false;
                            break;
                        case Key::W:
                            _gameModel->getLevel()->getAlly()->addLetter("w");
                            _letterPut = false;
                            break;
                        case Key::X:
                            _gameModel->getLevel()->getAlly()->addLetter("x");
                            _letterPut = false;
                            break;
                        case Key::Y:
                            _gameModel->getLevel()->getAlly()->addLetter("y");
                            _letterPut = false;
                            break;
                        case Key::Z:
                            _gameModel->getLevel()->getAlly()->addLetter("z");
                            _letterPut = false;
                            break;
                        case Key::Back:
                            _gameModel->getLevel()->getAlly()->deleteOneLetter();
                            _letterPut = false;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        if(_menu->getIntro())
        {
            if(time.GetElapsedTime()>=2)
            {
                _menu->setIntro(false);
                _menu->setMenu(true);
            }
        }
        else if(_menu->getMenu())
        {
            if(input.IsMouseButtonDown(Mouse::Left)){

                if(mouseX > 100 && mouseX < 295 && mouseY > 150 && mouseY < 180){
                    _menu->setGame(true);
                    _menu->setReady(true);
                    _menu->setLevel(true);
                    _menu->setMenu(false);
                    time.Reset();
                }
                else if(mouseX > 100 && mouseX < 200 && mouseY > 200 && mouseY < 230){
                    _menu->setOption(true);
                    _menu->setMenu(false);
                }
                else if(mouseX > 100 && mouseX < 200 && mouseY > 300 && mouseY < 330){
                    _menu->setCredits(true);
                    _menu->setMenu(false);
                }
                else if(mouseX > 100 && mouseX < 295 && mouseY > 350 && mouseY < 380){
                    _menu->setScore(true);
                    _menu->setMenu(false);
                }
                else if(mouseX > 100 && mouseX < 200 && mouseY > 550 && mouseY < 580){
                    result = false;
                }
            }
        }
        else if(_menu->getGame())
        {
            if(_menu->getLevel() && !_menu->getReady())
            {

                int x = _gameModel->getLevel()->getAlly()->getX();
                int y = _gameModel->getLevel()->getAlly()->getY();

                if(input.IsKeyDown(Key::Left))
                {
                    x -= _gameModel->getLevel()->getAlly()->getSpeedX();
                    _gameModel->getLevel()->getAlly()->move(x, y);
                }

                if(input.IsKeyDown(Key::Right))
                {
                    x += _gameModel->getLevel()->getAlly()->getSpeedX();
                    _gameModel->getLevel()->getAlly()->move(x, y);
                }

                if(input.IsKeyDown(Key::Up))
                {
                    y -= _gameModel->getLevel()->getAlly()->getSpeedY();
                    _gameModel->getLevel()->getAlly()->move(x, y);
                }

                if(input.IsKeyDown(Key::Down))
                {
                    y += _gameModel->getLevel()->getAlly()->getSpeedY();
                    _gameModel->getLevel()->getAlly()->move(x, y);
                }

                if(input.IsKeyDown(Key::Space))
                {
                    if(shoot.GetElapsedTime() >= _gameModel->getLevel()->getAlly()->getFireRate()){
                        _gameModel->getLevel()->getAlly()->shoot();
                        sound_shoot.Play();
                        shoot.Reset();
                    }
                }
                if(input.IsKeyDown(Key::V)){
                    if(shoot.GetElapsedTime() >= _gameModel->getLevel()->getAlly()->getFireRate()){
                        if(_gameModel->getLevel()->getAlly()->bonusShoot())
                            sound_bonusShoot.Play();
                        shoot.Reset();
                    }
                }
            }
            else if(_menu->getShop())
            {
                if(input.IsMouseButtonDown(Mouse::Left) || input.IsKeyDown(Key::Return)){
                    if(!_mouseClicked){
                        if((mouseX > 450) && (mouseX < 550)){
                            bool play = false;
                            if((mouseY>110) && (mouseY<130)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(0)){
                                    if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(0)){
                                        _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(0)->getPrice());
                                        _gameModel->getLevel()->getAlly()->getOneBulletBonus(0)->growPrice();
                                        play = true;
                                        _mouseClicked=true;
                                    }
                                }
                            }
                            if((mouseY>210) && (mouseY<230)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(1)){
                                    if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(1)){
                                        _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(1)->getPrice());
                                        _gameModel->getLevel()->getAlly()->getOneBulletBonus(1)->growPrice();
                                        play = true;
                                        _mouseClicked=true;
                                    }
                                }
                            }
                            if((mouseY>310) && (mouseY<330)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(2)){
                                    if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(2)){
                                        _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(2)->getPrice());
                                        _gameModel->getLevel()->getAlly()->getOneBulletBonus(2)->growPrice();
                                        play = true;
                                        _mouseClicked=true;
                                    }
                                }
                            }
                            if((mouseY>410) && (mouseY<430)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(3)){
                                    if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(3)){
                                        _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(3)->getPrice());
                                        _gameModel->getLevel()->getAlly()->getOneBulletBonus(3)->growPrice();
                                        play = true;
                                        _mouseClicked=true;
                                    }
                                }
                            }
                            if((mouseY>510) && (mouseY<530)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(4)){
                                    if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(4)){
                                        _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->getPrice());
                                        _gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->growPrice();
                                        play = true;
                                        _mouseClicked=true;
                                    }
                                }
                            }
                            if((mouseY>610) && (mouseY<630)){
                                if(_gameModel->getLevel()->getAlly()->getScore() > ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100 && _gameModel->getLevel()->getAlly()->getNumberOfLife()<5){
                                    _gameModel->getLevel()->getAlly()->reduceScore(ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100);
                                    _gameModel->getLevel()->getAlly()->setNumberOfLife(_gameModel->getLevel()->getAlly()->getNumberOfLife() + 1);
                                    _gameModel->getLevel()->getAlly()->setNumberLifeBuy(_gameModel->getLevel()->getAlly()->getNumberLifeBuy() + 1);
                                    play = true;
                                    _mouseClicked=true;
                                }
                            }

                            if((mouseY>150) && (mouseY<170)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(0)){
                                    play = true;
                                    _mouseClicked=true;
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(0)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->growPrice();
                                    _gameModel->getLevel()->getAlly()->changeBonus(0);
                                }
                            }
                            if((mouseY>250) && (mouseY<270)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(1)){
                                    play = true;
                                    _mouseClicked=true;
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(1)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->growPrice();
                                    _gameModel->getLevel()->getAlly()->changeBonus(1);
                                }
                            }
                            if((mouseY>350) && (mouseY<370)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(2)){
                                    play = true;
                                    _mouseClicked=true;
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(2)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->growPrice();
                                    _gameModel->getLevel()->getAlly()->changeBonus(2);
                                }
                            }
                            if((mouseY>450) && (mouseY<470)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(3)){
                                    play = true;
                                    _mouseClicked=true;
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(3)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->growPrice();
                                    _gameModel->getLevel()->getAlly()->changeBonus(3);
                                }
                            }
                            if((mouseY>550) && (mouseY<570)){
                                if(_gameModel->getLevel()->getAlly()->canBuyItem(4)){
                                    play = true;
                                    _mouseClicked=true;
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->growPrice();
                                    _gameModel->getLevel()->getAlly()->changeBonus(4);
                                }
                            }

                            if(play){
                                sound_iziMoney.Play();
                            }
                        }
                    }

                    if(((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
                    {
                        time.Reset();
                        _menu->setReady(true);
                        _menu->setLevel(true);
                        _menu->setShop(false);
                    }
                }
            }
            else if(_menu->getReady()){

            }
            else if (_menu->getSaveScore()){
                if(input.IsMouseButtonDown(Mouse::Left) || input.IsKeyDown(Key::Return)){
                    if((((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return)) && _gameModel->getLevel()->getAlly()->getName().size() > 0)
                    {
                        _menu->saveScore(_gameModel->getLevel()->getAlly()->getScore(), _gameModel->getLevel()->getAlly()->getName(), YOUR_FILE);
                        _menu->setSaveScore(false);
                    }
                }
            }
        }
        else if(_menu->getScore() || _menu->getCredits()){
            if(input.IsMouseButtonDown(Mouse::Left) || input.IsKeyDown(Key::Return)){
                if(((mouseX > SCREEN_WIDTH/2-90) && (mouseX < SCREEN_WIDTH/2+90) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
                {
                    _menu->setMenu(true);
                    _menu->setScore(false);
                    _menu->setOption(false);
                    _menu->setCredits(false);
                }
            }
        }
        else if(_menu->getOptions()){
            if(input.IsMouseButtonDown(Mouse::Left) || input.IsKeyDown(Key::Return)){
                if(mouseX>280 && mouseX<290){
                    if(mouseY>160 && mouseY<170){
                        _menu->setLanguage("francais");
                    }
                    else if (mouseY>140 && mouseY<150){
                        addShape(280, 140, 290, 140, 290, 150, 280, 150, true, false, 0, 5);
                        _menu->setLanguage("english");
                    }
                    else if (mouseY>180 && mouseY<190){
                        _menu->setLanguage("deutsch");
                    }
                }
                if(mouseX> 180 && mouseX<350 && mouseY>250 && mouseY<310){
                    _menu->setTheme(0);
                }
                if(mouseX> 180 && mouseX<280 && mouseY>340 && mouseY<430){
                    _menu->setTheme(1);
                }
                if(mouseY>500 && mouseY<520 && !_mouseClicked){
                    int dif = _gameModel->getDifficulty();

                    if(mouseX>250 && mouseX<270 && dif>0){
                        _gameModel->setDifficulty(dif-1);
                        _mouseClicked = true;
                    }
                    if(mouseX>420 && mouseX<440 && dif<10){
                        _gameModel->setDifficulty(dif+1);
                        _mouseClicked = true;
                    }
                }
                else if(((mouseX > SCREEN_WIDTH/2-90) && (mouseX < SCREEN_WIDTH/2+90) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
                {
                    _menu->setMenu(true);
                    _menu->setOption(false);
                }
            }
        }
        else if(_menu->getEnding())
        {

        }

    }
    return result;
}
