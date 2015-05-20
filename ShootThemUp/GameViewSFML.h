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

    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;

    sf::Sound sound_shoot;
    sf::Sound sound_iziMoney;
    sf::Sound sound_bonusShoot;


    GraphicLibrary* _graphicLibrary;
    float _yBackground;
    float _yBackground2;

    bool _letterPut;

    void showItems(int rang, int numPicture, std::string name, int width, int height, int price, int damage) const;

    void addText(std::string text, int x, int y, int size, int color) const;
    void addTextWithValue(int value, int xV, int yV, int sizeV ,std::string text, int xT, int yT, int sizeT, int color) const;
    void addShape(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool fill, bool outLine, int width, int color) const;

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
