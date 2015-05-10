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

using namespace sf;

GameViewSFML::GameViewSFML(){
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

void GameViewSFML::draw() const{
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
            Picture bg(_graphicLibrary->getImage(0), 0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
            _window->Draw(bg.getSprite());

            int k3 = _gameModel->getNumberTour()%3;
            int k2 = _gameModel->getNumberTour()%2;
                
            if(_gameModel->getLevel()->getEnemiesNumber() > 0)
            {
                for(auto e : _gameModel->getLevel()->getEnemies()){

                    int xe = e->getX();
                    int ye = e->getY();

                    if(e->getType()==1){
                        Picture en(_graphicLibrary->getImage(10), xe,ye,TINY_PICTURE_WIDTH,TINY_PICTURE_HEIGHT,0+(TINY_PICTURE_WIDTH/3)*k3,0,(TINY_PICTURE_WIDTH/3)+(TINY_PICTURE_WIDTH/3)*k3,TINY_PICTURE_HEIGHT);
                        _window->Draw(en.getSprite());
                        
                    }
                    else if(e->getType()==2){
                        Picture en(_graphicLibrary->getImage(11), xe,ye,SUBMARINE_PICTURE_WIDTH,SUBMARINE_PICTURE_HEIGHT,0+(SUBMARINE_PICTURE_WIDTH/2)*k2,0,(SUBMARINE_PICTURE_WIDTH/2)+(SUBMARINE_PICTURE_WIDTH/2)*k2,SUBMARINE_PICTURE_HEIGHT);
                        _window->Draw(en.getSprite());
                    }
                    else if(e->getType()==3){
                        Picture en(_graphicLibrary->getImage(21), xe,ye,MIGHTY_PICTURE_WIDTH,MIGHTY_PICTURE_HEIGHT,0+(MIGHTY_PICTURE_WIDTH/3)*k3,0,(MIGHTY_PICTURE_WIDTH/3)+(MIGHTY_PICTURE_WIDTH/3)*k3,MIGHTY_PICTURE_HEIGHT);
                        _window->Draw(en.getSprite());
                    }
                    
                    Shape cadreVieEnemy;
                    cadreVieEnemy.AddPoint(xe, ye+e->getHeight(), Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.AddPoint(xe+e->getWidth(), ye+e->getHeight(), Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.AddPoint(xe+e->getWidth(), ye+e->getHeight()+5, Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.AddPoint(xe, ye+e->getHeight()+5, Color(255, 255, 255), Color(255,255,255));
                    cadreVieEnemy.EnableFill(false);
                    cadreVieEnemy.EnableOutline(true);
                    cadreVieEnemy.SetOutlineWidth(1);
                    
                    _window->Draw(cadreVieEnemy);
                    
                    
                    
                    Shape vieEnemy;
                    vieEnemy.AddPoint(xe, ye+e->getHeight(), Color(240, 76, 36), Color(240, 76, 36));
                    
                    if(e->getType() == 1){
                        vieEnemy.AddPoint(xe + (((float)e->getHealth() / (float)TINY_LIFE) * (float)e->getWidth()), ye+e->getHeight(), Color(240, 76, 36), Color(240, 76, 36));
                        vieEnemy.AddPoint(xe + (((float)e->getHealth() / (float)TINY_LIFE) * (float)e->getWidth()), ye+e->getHeight()+5, Color(240, 76, 36), Color(240, 76, 36));
                    }
                    else if(e->getType() == 2){
                        vieEnemy.AddPoint(xe + (((float)e->getHealth() / (float)SUBMARINE_LIFE) * (float)e->getWidth()), ye+e->getHeight(), Color(240, 76, 36), Color(240, 76, 36));
                        vieEnemy.AddPoint(xe + (((float)e->getHealth() / (float)SUBMARINE_LIFE) * (float)e->getWidth()), ye+e->getHeight()+5, Color(240, 76, 36), Color(240, 76, 36));
                    }
                    else if(e->getType() == 3){
                        vieEnemy.AddPoint(xe + (((float)e->getHealth() / (float)MIGHTY_LIFE) * (float)e->getWidth()), ye+e->getHeight(), Color(240, 76, 36), Color(240, 76, 36));
                        vieEnemy.AddPoint(xe + (((float)e->getHealth() / (float)MIGHTY_LIFE) * (float)e->getWidth()), ye+e->getHeight()+5, Color(240, 76, 36), Color(240, 76, 36));
                    }
                    
                    vieEnemy.AddPoint(xe, ye+e->getHeight()+5, Color(240, 76, 36), Color(240, 76, 36));
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
                    cadreVieBoss.AddPoint(xb, yb+_gameModel->getLevel()->getBoss()->getHeight(), Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.AddPoint(xb+_gameModel->getLevel()->getBoss()->getWidth(), yb+_gameModel->getLevel()->getBoss()->getHeight(), Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.AddPoint(xb+_gameModel->getLevel()->getBoss()->getWidth(), yb+_gameModel->getLevel()->getBoss()->getHeight()+5, Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.AddPoint(xb, yb+_gameModel->getLevel()->getBoss()->getHeight()+5, Color(255, 255, 255), Color(255,255,255));
                    cadreVieBoss.EnableFill(false);
                    cadreVieBoss.EnableOutline(true);
                    cadreVieBoss.SetOutlineWidth(1);
                    
                    _window->Draw(cadreVieBoss);
                    
                    Shape vieBoss;
                    vieBoss.AddPoint(xb, yb+_gameModel->getLevel()->getBoss()->getHeight(), Color(240, 76, 36), Color(240, 76, 36));
                    std::cout << (float)_gameModel->getLevel()->getBoss()->getHealth() << std::endl;
                    vieBoss.AddPoint(xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / (float)BOSS_LIFE) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb+_gameModel->getLevel()->getBoss()->getHeight(), Color(240, 76, 36), Color(240, 76, 36));
                    vieBoss.AddPoint(xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / (float)BOSS_LIFE) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb+_gameModel->getLevel()->getBoss()->getHeight()+5, Color(240, 76, 36), Color(240, 76, 36));
                    vieBoss.AddPoint(xb, yb+_gameModel->getLevel()->getBoss()->getHeight()+5, Color(240, 76, 36), Color(240, 76, 36));
                    vieBoss.EnableFill(true);
                    vieBoss.EnableOutline(false);
                    
                    _window->Draw(vieBoss);
                  
                }
            }

            if(_gameModel->getLevel()->getNumberOfBullets() > 0){
                for(auto b : _gameModel->getLevel()->getBullets()){
                    int xba = b->getX();
                    int yba = b->getY();
                    
                    if(b->getType() == 0){
                        Picture bba(_graphicLibrary->getImage(12), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());
                    }
                    else if(b->getType() == 1){
                        Picture bba(_graphicLibrary->getImage(5), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());

                    }
                    else if(b->getType() == 2){
                        Picture bba(_graphicLibrary->getImage(18), xba,yba,b->getWidth(),b->getHeight());
                        _window->Draw(bba.getSprite());

                    }
                    else if(b->getType() == 3){
                        Picture bba(_graphicLibrary->getImage(23), xba,yba,b->getWidth(),b->getHeight());
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
            
            #ifdef __linux__
            if(_gameModel->getLevel()->getAlly() != nullptr){
            #else
            if(_gameModel->getLevel()->getAlly() != 0){
            #endif
                int xp = _gameModel->getLevel()->getAlly()->getX();
                int yp = _gameModel->getLevel()->getAlly()->getY();
                Picture ally(_graphicLibrary->getImage(17), xp,yp,ALLY_PICTURE_WIDTH,ALLY_PICTURE_HEIGHT,0+(ALLY_PICTURE_WIDTH/3)*k3,0,(ALLY_PICTURE_WIDTH/3)+(ALLY_PICTURE_WIDTH/3)*k3,ALLY_PICTURE_HEIGHT);
                _window->Draw(ally.getSprite());
                
                for(int i = 0; i<_gameModel->getLevel()->getAlly()->getNumberOfLife(); i++){
                    Picture life(_graphicLibrary->getImage(25), i*25,5,20,20);
                    _window->Draw(life.getSprite());
                }
            }
        }
        if(_menu->getShop())
        {

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
        else if(_menu->getScore())
        {
            
        }
        else if(_menu->getSaveScore())
        {
            _menu->setMenu(true);
        }
        else if(_menu->getEnding())
        {
            
        }
        
        else if(_menu->getShop())
        {
            _menu->setLevel(true);
            _menu->setShop(false);
        }
        
        else if(_menu->getMenu())
        {
            if(input.IsMouseButtonDown(Mouse::Left)){
                
                int mouseX = input.GetMouseX();
                int mouseY = input.GetMouseY();
                
                if(mouseX >= 100 && mouseX <= 200 && mouseY >= 150 && mouseY <= 170){
                    _menu->setGame(true);
                    _menu->setLevel(true);
                    _menu->setMenu(false);
                }
                else if(mouseX >= 100 && mouseX <= 200 && mouseY >= 190 && mouseY <= 210){
                    result=false;
                }
                else if(mouseX >= 100 && mouseX <= 200 && mouseY >= 300 && mouseY <= 320){
                    //std::cout << "nice 3" << std::endl;
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
            }
        }
    }
    return result;
}
