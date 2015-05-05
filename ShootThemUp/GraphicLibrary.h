//
//  GameViewSFML.h
//  ShootThemUp
//
//  Created by Nicolas on 28/04/2015.
//  Copyright (c) 2015 Nicolas. All rights reserved.
//

#ifndef GRAPHICLIBRARY_H_INCLUDED
#define GRAPHICLIBRARY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class GraphicLibrary{
private:
    std::vector<sf::Image *> _imagesList;

public:
    GraphicLibrary();
    ~GraphicLibrary();

    void loadLibrary();

    sf::Image * getImage(int i) const;

};

#endif // GRAPHICLIBRARY_H_INCLUDED
