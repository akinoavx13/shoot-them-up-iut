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
}

GameViewSFML::~GameViewSFML(){
    delete _menu;
    delete _window;
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
        showIntroSFML();
    }

    else if(_menu->getMenu())
    {

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

void GameViewSFML::showIntroSFML() const{

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
