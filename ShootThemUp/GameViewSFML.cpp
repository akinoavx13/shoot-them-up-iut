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
    _window = new RenderWindow(VideoMode(MODEL_HEIGHT, MODEL_WIDTH), "Shmup");
    _window->SetFramerateLimit(15);
    _gameModel = nullptr;
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
        Picture * bg = new Picture(_graphicLibrary->getImage(22), 0,0,MODEL_HEIGHT,MODEL_WIDTH);
        _window->Draw(bg->getSprite());

        if(time.GetElapsedTime()>=3)
        {
            _menu->setIntro(false);
            _menu->setMenu(true);
        }
    }

    else if(_menu->getMenu())
    {
        Picture * button1 = new Picture(_graphicLibrary->getImage(15), 100,150,100,20);
        _window->Draw(button1->getSprite());

        Picture * button2 = new Picture(_graphicLibrary->getImage(14), 100,190,55,20);
        _window->Draw(button2->getSprite());

        Picture * button3 = new Picture(_graphicLibrary->getImage(2), 100,300,80,20);
        _window->Draw(button3->getSprite());


    }

    else if(_menu->getGame())
    {
        if(_menu->getLevel())
        {
            Picture * bg = new Picture(_graphicLibrary->getImage(0), 0,0,MODEL_HEIGHT,MODEL_WIDTH);
            _window->Draw(bg->getSprite());

            int xp = _gameModel->getLevel()->getAlly()->getX();
            int yp = _gameModel->getLevel()->getAlly()->getY();

            int k3 = _gameModel->getNumberTour()%3;
            int k2 = _gameModel->getNumberTour()%2;

            Picture * ally = new Picture(_graphicLibrary->getImage(17), xp,yp,ALLY_PICTURE_WIDTH,ALLY_PICTURE_HEIGHT,0+(ALLY_PICTURE_WIDTH/3)*k3,0,(ALLY_PICTURE_WIDTH/3)+(ALLY_PICTURE_WIDTH/3)*k3,ALLY_PICTURE_HEIGHT);
            _window->Draw(ally->getSprite());

            if(_gameModel->getLevel()->getEnemiesNumber() > 0)
            {
                for(auto e : _gameModel->getLevel()->getEnemies()){

                    int xe = e->getX();
                    int ye = e->getY();
                    std::cout << e->getType() << std::endl;

                    Picture * en;
                    if(e->getType()==1){
                        en = new Picture(_graphicLibrary->getImage(10), xe,ye,TINY_PICTURE_WIDTH,TINY_PICTURE_HEIGHT,0+(TINY_PICTURE_WIDTH/3)*k3,0,(TINY_PICTURE_WIDTH/3)+(TINY_PICTURE_WIDTH/3)*k3,TINY_PICTURE_HEIGHT);
                    }
                    else if(e->getType()==2){
                        en = new Picture(_graphicLibrary->getImage(11), xe,ye,SUBMARINE_PICTURE_WIDTH,SUBMARINE_PICTURE_HEIGHT,0+(SUBMARINE_PICTURE_WIDTH/2)*k2,0,(SUBMARINE_PICTURE_WIDTH/2)+(SUBMARINE_PICTURE_WIDTH/2)*k2,SUBMARINE_PICTURE_HEIGHT);
                    }
                    else if(e->getType()==3){
                        en = new Picture(_graphicLibrary->getImage(21), xe,ye,MIGHTY_PICTURE_WIDTH,MIGHTY_PICTURE_HEIGHT,0+(MIGHTY_PICTURE_WIDTH/3)*k3,0,(MIGHTY_PICTURE_WIDTH/3)+(MIGHTY_PICTURE_WIDTH/3)*k3,MIGHTY_PICTURE_HEIGHT);
                    }
                    _window->Draw(en->getSprite());
                }
            }

            if(_gameModel->getLevel()->getEnemiesNumber() <= 0)
            {
                if(_gameModel->getLevel()->getBoss() != nullptr)
                {
                    int xb = _gameModel->getLevel()->getBoss()->getX();
                    int yb = _gameModel->getLevel()->getBoss()->getY();
                    Picture * b = new Picture(_graphicLibrary->getImage(1), xb,yb,294,98, 0+98*k3,0,98+98*k3,98);
                    _window->Draw(b->getSprite());
                }
            }

            for(auto b : _gameModel->getLevel()->getBullets()){
                int xba = b->getX();
                int yba = b->getY();
                Picture * bba = new Picture(_graphicLibrary->getImage(12), xba,yba,32,32);
                _window->Draw(bba->getSprite());
            }


            for(int i = 0; i<_gameModel->getLevel()->getAlly()->getNumberOfLife(); i++){
                Picture * life = new Picture(_graphicLibrary->getImage(17), i*25,5,20,20);
                _window->Draw(life->getSprite());
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

            if(_menu->getIntro())
            {

            }

            else if(_menu->getMenu())
            {
                if(Event.Type == Event::MouseButtonPressed){
                    if((Event.MouseButton.X>=100) & (Event.MouseButton.X<=200) & (Event.MouseButton.Y>=150) & (Event.MouseButton.Y<=170)){
                        _menu->setGame(true);
                        _menu->setLevel(true);
                        _menu->setMenu(false);
                    }
                    else if((Event.MouseButton.X>=100) & (Event.MouseButton.X<=200) & (Event.MouseButton.Y>=190) & (Event.MouseButton.Y<=210)){
                        result=false;
                    }
                    else if((Event.MouseButton.X>=100) & (Event.MouseButton.X<=200) & (Event.MouseButton.Y>=300) & (Event.MouseButton.Y<=320)){
                        std::cout << "nice 3" << std::endl;
                    }
                }
            }

            else if(_menu->getGame())
            {
                if(_menu->getLevel())
                {
                    if(Event.Type == Event::KeyPressed){
                        int x = _gameModel->getLevel()->getAlly()->getX();
                        int y = _gameModel->getLevel()->getAlly()->getY();
                        if(Event.Key.Code == Key::Left){
                            x-=5;
                        }
                        else if(Event.Key.Code == Key::Right){
                            x+=5;
                        }

                        if(Event.Key.Code == Key::Up){
                            y-=5;
                        }
                        else if(Event.Key.Code == Key::Down){
                            y+=5;
                        }
                        _gameModel->getLevel()->getAlly()->move(x, y);

                        if(Event.Key.Code == Key::Space){
                            _gameModel->getLevel()->getAlly()->shoot();
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
        }
    }
    return result;
}
