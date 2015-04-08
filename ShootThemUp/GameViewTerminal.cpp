//
//  GameView.cpp
//  ShootThemUp
//
//  Created by Maxime Maheo on 05/03/2015.
//  Copyright (c) 2015 Maxime Maheo. All rights reserved.
//

#include "GameViewTerminal.h"

using namespace std;

/*
 * default constructor
 */
GameViewTerminal::GameViewTerminal(): _gameModel(nullptr){
    _menu = new Menu();
}

/*
 * destructor
 */
GameViewTerminal::~GameViewTerminal(){
    delete _menu;
}

//----------METHODS----------

/*
 * principal methods to draw. Show variables values
 * info : constant
 */
void GameViewTerminal::draw() const{
    if(_menu->getIntro()) {
        _menu->showIntro();
    }
    
    if(_menu->getMenu()){
        cout << "---- Menu ----" << endl
        << "1) Jouer" << endl
        << "2) Scores" << endl
        << "3) Quitter" << endl ;
        
        char choice;
        cin >> choice;
        switch (choice) {
            case '1':
                _menu->setGame(true);
                _menu->setLevel(true);
                _menu->setMenu(false);
                break;
            
            case '2':
                _menu->setScore(true);
                _menu->setMenu(false);
                break;
                
            case '3':
                _menu->setEnding(true);
                _menu->setMenu(false);
                break;
            default:
                cout << "Mauvais choix" << endl;
                break;
        }
    }
    
    if(_menu->getGame()) {
        if(_menu->getLevel()) {
            cout << "Informations sur le niveau" << endl;
            cout << "\tNiveau : " << _gameModel->getLevel()->getLevelNumber() << endl;
            cout << "\tTour n° : " << _gameModel->getNumberTour() << endl;
            cout << "\tNombre d'ennemis : " << _gameModel->getLevel()->getEnemiesNumber() << endl;
            cout << "\tVos dégats : " << MAIN_SHOOT_DAMAGE << endl;
            cout << "\tPortée du tir : " << DEFAULT_SHIP_OFFSET_SHOOT << endl << endl;
            
            cout << _gameModel->getLevel()->getAlly()->toString() << endl;
            
            if(_gameModel->getLevel()->getEnemiesNumber() > 0){
                cout << _gameModel->getLevel()->toString() << endl;
            }

            if(_gameModel->getLevel()->getEnemiesNumber() <= 0){
                if(_gameModel->getLevel()->getBoss() != nullptr){
                    cout << _gameModel->getLevel()->getBoss()->toString() << endl;
                }
            }
            
            char choice;
            float posX;
            float posY;
            
            cout << "Quel voulez vous faire ?" << endl;
            cout << "\t1) Tirer sur un ennemi" << endl;
            cout << "\t2) Bouger" << endl;
            cout << "Votre choix : ";
            cin >> choice;
            
            switch (choice) {
                case '1':
                    _gameModel->getLevel()->getAlly()->shoot();
                    break;
                    
                case '2':
                    cout << "Entrer les nouvelles position : " << endl;
                    cout << "position X : ";
                    cin >> posX;
                    cout << "position Y : ";
                    cin >> posY;
                    _gameModel->getLevel()->getAlly()->move(posX, posY);
                    break;
                    
                default:
                    cout << "Mauvais choix" << endl;
                    break;
            }
        }
        if(_menu->getShop()){
            cout << "Bienvenue dans le shop" << endl;
            char choice;
            cin >> choice;
            switch (choice) {
                default:
                    _menu->setShop(false);
                    _menu->setLevel(true);
                    break;
            }
        }
    }
    
    if(_menu->getEnding()){
        cout << "La partie est fini" << endl;
    }
}


//----------SETTERS----------
/*
 * params : game model
 */
void GameViewTerminal::setModel(GameModel *gameModel){
    _gameModel = gameModel;
}

bool GameViewTerminal::treatEvent(){
    return _menu->getEnding();
}

void GameViewTerminal::setModelMenu(){
    _gameModel->setMenu(_menu);
}



