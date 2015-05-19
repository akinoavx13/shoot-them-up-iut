//
//  GameViewSFML.h
//  ShootThemUp
//
//  Created by Nicolas on 28/04/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#ifndef GAMEVIEWSFML_H_INCLUDED
#define GAMEVIEWSFML_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "GameModel.h"
#include "Menu.h"
#include "GraphicLibrary.h"
#include <SFML/Audio.hpp>

class GameViewSFML{
private:
    sf::RenderWindow * _window;

    GameModel* _gameModel;
    Menu* _menu;

    sf::Clock time;
    sf::Clock shoot;
    
    sf::Font font;
    
    sf::SoundBuffer Buffer;
    sf::Sound Sound;


    GraphicLibrary* _graphicLibrary;
    float _yBackground;
    float _yBackground2;
    
    bool _letterPut;
    
    void showItems(int rang, int numPicture, std::string name, int width, int height, int price, int damage) const;
    
    void addText(std::string text, int x, int y, int size) const;
    void addTextWithValue(int value, int xV, int yV, int sizeV ,std::string text, int xT, int yT, int sizeT) const;
public:
    //CONSTRUCTOR
    GameViewSFML();

    //DESTRUCTOR
    ~GameViewSFML();

    //METHODS
    void draw();

    //SETTERS
    void setModel(GameModel* gameModel);
    void setModelMenu();
    
    bool treatEvent();

};

#endif // GAMEVIEWSFML_H_INCLUDED
