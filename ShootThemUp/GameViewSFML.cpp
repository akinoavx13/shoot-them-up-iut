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
    _window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Shmup");
    _window->SetFramerateLimit(SCREEN_FPS);
    #ifdef __linux__
    _gameModel = nullptr;
    #else
    _gameModel = 0;
    #endif
    _graphicLibrary = new GraphicLibrary();
    _graphicLibrary->loadLibrary();
    time.Reset();
    
    if(!font.LoadFromFile("police.ttf")){
        cout << "The font can't be load" << endl;
    }
    
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
    _window->Clear();
    if(_menu->getIntro())
    {
        Picture bg(_graphicLibrary->getImage(22), 0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        _window->Draw(bg.getSprite());
        
        if(time.GetElapsedTime()>=1)
        {
            _menu->setIntro(false);
            _menu->setMenu(true);
        }
    }

    else if(_menu->getMenu())
    {
        Picture button1(_graphicLibrary->getImage(15), 100,150,100,20);
        _window->Draw(button1.getSprite());

        Picture button2(_graphicLibrary->getImage(14), 100,190,55,20);
        _window->Draw(button2.getSprite());

        Picture button3(_graphicLibrary->getImage(2), 100,300,80,20);
        _window->Draw(button3.getSprite());
    }

    else if(_menu->getGame())
    {
        if(_menu->getLevel())
        {
            Picture bg(_graphicLibrary->getImage(0), 0,_yBackground,MODEL_WIDTH,MODEL_HEIGHT);
            Picture bg2(_graphicLibrary->getImage(0), 0,_yBackground2,MODEL_WIDTH,MODEL_HEIGHT);

            _window->Draw(bg.getSprite());
            _window->Draw(bg2.getSprite());

            if(_yBackground > MODEL_HEIGHT - 5){
                _yBackground = -MODEL_HEIGHT + 2;
            }
            
            if(_yBackground2 > MODEL_HEIGHT - 5){
                _yBackground2 = -MODEL_HEIGHT + 2;
            }

            _yBackground += 0.5;
            _yBackground2 += 0.5;

            int k3 = _gameModel->getNumberTour()%3;
            int k2 = _gameModel->getNumberTour()%2;
                
            if(_gameModel->getLevel()->getEnemiesNumber() > 0)
            {
                for(auto e : _gameModel->getLevel()->getEnemies())
                {
                    int xe = e->getX();
                    int ye = e->getY();

                    if(e->getType()==1)
                    {
                        Picture en(_graphicLibrary->getImage(10), xe,ye,TINY_PICTURE_WIDTH,TINY_PICTURE_HEIGHT,0+(TINY_PICTURE_WIDTH/3)*k3,0,(TINY_PICTURE_WIDTH/3)+(TINY_PICTURE_WIDTH/3)*k3,TINY_PICTURE_HEIGHT);
                        _window->Draw(en.getSprite());
                    }
                    else if(e->getType()==2)
                    {
                        Picture en(_graphicLibrary->getImage(11), xe,ye,SUBMARINE_PICTURE_WIDTH,SUBMARINE_PICTURE_HEIGHT,0+(SUBMARINE_PICTURE_WIDTH/2)*k2,0,(SUBMARINE_PICTURE_WIDTH/2)+(SUBMARINE_PICTURE_WIDTH/2)*k2,SUBMARINE_PICTURE_HEIGHT);
                        _window->Draw(en.getSprite());
                    }
                    else if(e->getType()==3)
                    {
                        Picture en(_graphicLibrary->getImage(21), xe,ye,MIGHTY_PICTURE_WIDTH,MIGHTY_PICTURE_HEIGHT,0+(MIGHTY_PICTURE_WIDTH/3)*k3,0,(MIGHTY_PICTURE_WIDTH/3)+(MIGHTY_PICTURE_WIDTH/3)*k3,MIGHTY_PICTURE_HEIGHT);
                        _window->Draw(en.getSprite());
                    }
                    
                    Shape cadreVieEnemy;
                    cadreVieEnemy.AddPoint(xe, ye-15, Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.AddPoint(xe+e->getWidth(), ye-15, Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.AddPoint(xe+e->getWidth(), ye-10, Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.AddPoint(xe, ye-10, Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.EnableFill(false);
                    cadreVieEnemy.EnableOutline(true);
                    cadreVieEnemy.SetOutlineWidth(1);
                    
                    _window->Draw(cadreVieEnemy);
                    
                    
                    
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
                    Picture b(_graphicLibrary->getImage(1), xb,yb,BOSS_PICTURE_WIDTH, BOSS_PICTURE_HEIGHT, 0+(BOSS_PICTURE_WIDTH/3)*k3,0,(BOSS_PICTURE_WIDTH/3)+(BOSS_PICTURE_WIDTH/3)*k3,BOSS_PICTURE_HEIGHT);
                    _window->Draw(b.getSprite());
                    
                    Shape cadreVieBoss;
                    cadreVieBoss.AddPoint(xb, yb-15, Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.AddPoint(xb+_gameModel->getLevel()->getBoss()->getWidth(), yb-15, Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.AddPoint(xb+_gameModel->getLevel()->getBoss()->getWidth(), yb-10, Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.AddPoint(xb, yb-10, Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.EnableFill(false);
                    cadreVieBoss.EnableOutline(true);
                    cadreVieBoss.SetOutlineWidth(1);
                    
                    _window->Draw(cadreVieBoss);
                    
                    Shape vieBoss;
                    vieBoss.AddPoint(xb, yb-15, Color(240, 76, 36), Color(240, 76, 36));
                    //std::cout << (float)_gameModel->getLevel()->getBoss()->getHealth() << std::endl;
                    vieBoss.AddPoint(xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / ((float)BOSS_LIFE + (_gameModel->getLevel()->getLevelNumber()-1) *30)) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb-15, Color(240, 76, 36), Color(240, 76, 36));
                    vieBoss.AddPoint(xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / ((float)BOSS_LIFE + (_gameModel->getLevel()->getLevelNumber()-1) *30)) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb-10, Color(240, 76, 36), Color(240, 76, 36));
                    vieBoss.AddPoint(xb, yb-10, Color(240, 76, 36), Color(240, 76, 36));
                    vieBoss.EnableFill(true);
                    vieBoss.EnableOutline(false);
                    
                    _window->Draw(vieBoss);
                  
                }
            }

            if(_gameModel->getLevel()->getNumberOfBullets() > 0)
            {
                for(auto b : _gameModel->getLevel()->getBullets())
                {
                    int xba = b->getX();
                    int yba = b->getY();
                    
                    if(b->getType() == 0)
                    {
                        Picture bba(_graphicLibrary->getImage(12), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());
                    }
                    else if(b->getType() == 1)
                    {
                        Picture bba(_graphicLibrary->getImage(5), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());

                    }
                    else if(b->getType() == 2)
                    {
                        Picture bba(_graphicLibrary->getImage(18), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());

                    }
                    else if(b->getType() == 3)
                    {
                        Picture bba(_graphicLibrary->getImage(23), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());
                    }
                    else if(b->getType() == 4)
                    {
                        Picture bba(_graphicLibrary->getImage(4), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());
                    }
                }
            }
                
            Shape cadreVie;
            cadreVie.AddPoint(100, 10, Color(255, 255, 255), Color(255,255,255));
            cadreVie.AddPoint(200, 10, Color(255, 255, 255), Color(255,255,255));
            cadreVie.AddPoint(200, 20, Color(255, 255, 255), Color(255,255,255));
            cadreVie.AddPoint(100, 20, Color(255, 255, 255), Color(255,255,255));
            cadreVie.EnableFill(false);
            cadreVie.EnableOutline(true);
            cadreVie.SetOutlineWidth(2);
            
            _window->Draw(cadreVie);
            
            Shape vie;
            vie.AddPoint(100, 10, Color(240, 76, 36), Color(240, 76, 36));
            vie.AddPoint(100 + (((float)_gameModel->getLevel()->getAlly()->getHealth() / (float)ALLY_LIFE) * (float)100), 10, Color(240, 76, 36), Color(240, 76, 36));
            vie.AddPoint(100 + (((float)_gameModel->getLevel()->getAlly()->getHealth() / (float)ALLY_LIFE) * (float)100), 20, Color(240, 76, 36), Color(240, 76, 36));
            vie.AddPoint(100, 20, Color(240, 76, 36), Color(240, 76, 36));
            vie.EnableFill(true);
            vie.EnableOutline(false);
            vie.SetOutlineWidth(0);
            
            _window->Draw(vie);
            
            //
            String textScore("SCORE : ", font , 15);
            textScore.SetX(SCREEN_WIDTH - 150);
            textScore.SetY(5);
            textScore.SetColor(Color(255, 255, 255));
            _window->Draw(textScore);
            
            std::string valeur;
            std::stringstream out;
            out << _gameModel->getLevel()->getAlly()->getScore();
            valeur = out.str();
            
            String valeurScore(valeur, font , 15);
            valeurScore.SetX(SCREEN_WIDTH - 70);
            valeurScore.SetY(5);
            valeurScore.SetColor(Color(255, 255, 255));
            _window->Draw(valeurScore);
            
            //
            String textLevel("NIVEAU : ", font , 15);
            textLevel.SetX(SCREEN_WIDTH - 150);
            textLevel.SetY(20);
            textLevel.SetColor(Color(255, 255, 255));
            _window->Draw(textLevel);
            
            std::string valeurNiveau;
            std::stringstream out2;
            out2 << _gameModel->getLevel()->getLevelNumber();
            valeurNiveau = out2.str();
            
            String valeurLevel(valeurNiveau, font , 15);
            valeurLevel.SetX(SCREEN_WIDTH - 70);
            valeurLevel.SetY(20);
            valeurLevel.SetColor(Color(255, 255, 255));
            _window->Draw(valeurLevel);
            
            //
            String textBonus("TIRS BONUS : ", font , 15);
            textBonus.SetX(SCREEN_WIDTH - 150);
            textBonus.SetY(35);
            textBonus.SetColor(Color(255, 255, 255));
            _window->Draw(textBonus);
            
            std::string valeurBonusShoot;
            std::stringstream out3;
            out3 << _gameModel->getLevel()->getAlly()->getNumberShootBonusMax()-_gameModel->getLevel()->getAlly()->getNumberShootBonus();
            valeurBonusShoot = out3.str();
            
            String textBonusShoot(valeurBonusShoot, font , 15);
            textBonusShoot.SetX(SCREEN_WIDTH - 20);
            textBonusShoot.SetY(35);
            textBonusShoot.SetColor(Color(255, 255, 255));
            _window->Draw(textBonusShoot);
            
            #ifdef __linux__
            if(_gameModel->getLevel()->getAlly() != nullptr){
            #else
            if(_gameModel->getLevel()->getAlly() != 0){
            #endif
                int xp = _gameModel->getLevel()->getAlly()->getX();
                int yp = _gameModel->getLevel()->getAlly()->getY();
                Picture ally(_graphicLibrary->getImage(17), xp,yp,ALLY_PICTURE_WIDTH,ALLY_PICTURE_HEIGHT,0+(ALLY_PICTURE_WIDTH/3)*k3,0,(ALLY_PICTURE_WIDTH/3)+(ALLY_PICTURE_WIDTH/3)*k3,ALLY_PICTURE_HEIGHT);
                _window->Draw(ally.getSprite());
                
                for(int i = 0; i<_gameModel->getLevel()->getAlly()->getNumberOfLife(); i++)
                {
                    Picture life(_graphicLibrary->getImage(25), i*25,5,20,20);
                    _window->Draw(life.getSprite());
                }
            }
        }
        
        if(_menu->getShop())
        {
            Picture standard(_graphicLibrary->getImage((12)), 75 , 65, STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT);
            _window->Draw(standard.getSprite());
            
            sf::Shape Line1 = sf::Shape::Line(0, 100, SCREEN_WIDTH, 100 , 1, Color(255, 255, 255));
            _window->Draw(Line1);
            
            Picture fireBall(_graphicLibrary->getImage((5)), 70, 140, FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT);
            _window->Draw(fireBall.getSprite());
            
            sf::Shape Line2 = sf::Shape::Line(0, 180, SCREEN_WIDTH, 180 , 1, Color(255, 255, 255));
            _window->Draw(Line2);
            
            Picture littleLaser(_graphicLibrary->getImage((18)), 75, 205, 9, 20);
            _window->Draw(littleLaser.getSprite());
            
            sf::Shape Line3 = sf::Shape::Line(0, 260, SCREEN_WIDTH, 260 , 1, Color(255, 255, 255));
            _window->Draw(Line3);
            
            Picture doubleLaser(_graphicLibrary->getImage((4)), 72, 290, 17, 16);
            _window->Draw(doubleLaser.getSprite());
            
            sf::Shape Line4 = sf::Shape::Line(0, 340, SCREEN_WIDTH, 340 , 1, Color(255, 255, 255));
            _window->Draw(Line4);
            
            Picture bigLaser(_graphicLibrary->getImage((23)), 75, 365, 9, 30);
            _window->Draw(bigLaser.getSprite());
            
            sf::Shape Line5 = sf::Shape::Line(0, 420, SCREEN_WIDTH, 420 , 1, Color(255, 255, 255));
            _window->Draw(Line5);
            
            Picture life(_graphicLibrary->getImage((25)), 70, 440, 20, 20);
            _window->Draw(life.getSprite());
            

            
            Shape cadreFinLevel;
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-50, Color(255, 255, 255), Color(255,255,255));
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2+75, SCREEN_HEIGHT-50, Color(255, 255, 255), Color(255,255,255));
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2+75, SCREEN_HEIGHT-20, Color(255, 255, 255), Color(255,255,255));
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-20, Color(255, 255, 255), Color(255,255,255));
            
            cadreFinLevel.EnableFill(false);
            cadreFinLevel.EnableOutline(true);
            cadreFinLevel.SetOutlineWidth(2);
            
            _window->Draw(cadreFinLevel);
            
            String nextLevel("NEXT LEVEL", font , 20);
            nextLevel.SetX(SCREEN_WIDTH/2-60);
            nextLevel.SetY(SCREEN_HEIGHT-45);
            nextLevel.SetColor(Color(255, 255, 255));
            _window->Draw(nextLevel);
        }
    }

    else if(_menu->getScore())
    {

    }
    else if(_menu->getSaveScore())
    {

    }
    else if(_menu->getEnding())
    {

    }
    _window->Display();
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
        }
        
        if(_menu->getIntro())
        {
            
        }
        else if(_menu->getMenu())
        {
            if(input.IsMouseButtonDown(Mouse::Left)){
                if(mouseX >= 100 && mouseX <= 200 && mouseY >= 150 && mouseY <= 170){
                    _menu->setGame(true);
                    _menu->setLevel(true);
                    _menu->setMenu(false);
                }
                else if(mouseX >= 100 && mouseX <= 200 && mouseY >= 190 && mouseY <= 210){
                    result=false;
                }
                else if(mouseX >= 100 && mouseX <= 200 && mouseY >= 300 && mouseY <= 320){
                    
                }
            }
        }
        else if(_menu->getGame())
        {
            if(_menu->getLevel())
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
                        shoot.Reset();
                    }
                }
                if(input.IsKeyDown(Key::A))
                {
                    if(shoot.GetElapsedTime() >= _gameModel->getLevel()->getAlly()->getFireRate()){
                        _gameModel->getLevel()->getAlly()->bonusShoot();
                        shoot.Reset();
                    }
                }
            }
            else if(_menu->getShop())
            {
                if(input.IsMouseButtonDown(Mouse::Left) || input.IsKeyDown(Key::Return)){
                    if(((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
                    {
                        _menu->setLevel(true);
                        _menu->setShop(false);
                    }
                }
            }
        }

        else if(_menu->getSaveScore())
        {
            //_menu->setMenu(true);
        }
        else if(_menu->getEnding())
        {
            
        }
        else if(_menu->getScore())
        {
            
        }
        
    }
    return result;
}
