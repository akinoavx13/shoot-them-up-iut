//
//  GameViewSFML.cpp
//  ShootThemUp
//
//  Created by Nicolas on 28/04/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#include "GameViewSFML.h"
#include "const.h"

using namespace sf;

GameViewSFML::GameViewSFML(){
    _menu = new Menu();
    _window = new RenderWindow(VideoMode(MODEL_HEIGHT, MODEL_WIDTH), "Shmup");
    _gameModel = nullptr;
    _graphicLibrary = new GraphicLibrary();
    _graphicLibrary->loadLibrary();
    _tmp=0;
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
        Clock time;
        Image backgroundImage;
        Sprite backgroundSprite;

        backgroundImage=_graphicLibrary->getImage(22);
        backgroundSprite.SetImage(backgroundImage);
        backgroundSprite.SetX(0);
        backgroundSprite.SetY(0);
        backgroundSprite.Resize(MODEL_HEIGHT, MODEL_WIDTH);

        _window->Draw(backgroundSprite);

        std::cout << time.GetElapsedTime() << std::endl;
        std::cout << "\t" << _menu->getTime() << std::endl;
        if(_menu->getTime()>=2)
        {
            _menu->setIntro(false);
            _menu->setMenu(true);
        }
        else{
            _menu->setTime(time.GetElapsedTime());

        }
    }

    else if(_menu->getMenu())
    {
        Image backgroundImage;
        Sprite backgroundSprite;

        backgroundImage=_graphicLibrary->getImage(0);
        backgroundSprite.SetImage(backgroundImage);
        backgroundSprite.SetX(0);
        backgroundSprite.SetY(0);
        backgroundSprite.Resize(MODEL_HEIGHT, MODEL_WIDTH);

        _window->Draw(backgroundSprite);
    }

    else if(_menu->getGame())
    {
        if(_menu->getLevel())
        {

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
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)){
                _window->Close();
                result = false;
            }
        }
    }
    return result;
}

void GameViewSFML::setTime(float time){
    _tmp+=time;
}
