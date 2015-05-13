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
            textBonus.SetY(55);
            textBonus.SetColor(Color(255, 255, 255));
            _window->Draw(textBonus);
            
            std::string valeurBonusShoot;
            std::stringstream out3;
            out3 << _gameModel->getLevel()->getAlly()->getNumberShootBonusMax()-_gameModel->getLevel()->getAlly()->getNumberShootBonus();
            valeurBonusShoot = out3.str();
            
            String textBonusShoot(valeurBonusShoot, font , 15);
            textBonusShoot.SetX(SCREEN_WIDTH - 35);
            textBonusShoot.SetY(55);
            textBonusShoot.SetColor(Color(255, 255, 255));
            _window->Draw(textBonusShoot);
            
            String textPower("POWER : ", font , 15);
            textPower.SetX(SCREEN_WIDTH - 150);
            textPower.SetY(70);
            textPower.SetColor(Color(255, 255, 255));
            _window->Draw(textPower);
            
            std::string valeurPower;
            std::stringstream out4;
            out4 << _gameModel->getLevel()->getAlly()->getBulletBonus()->getDamage();
            valeurBonusShoot = out4.str();
            
            String textValeurPower(valeurBonusShoot, font , 15);
            textValeurPower.SetX(SCREEN_WIDTH - 35);
            textValeurPower.SetY(70);
            textValeurPower.SetColor(Color(255, 255, 255));
            _window->Draw(textValeurPower);
            
            if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 0)
            {
                Picture v1(_graphicLibrary->getImage(12), SCREEN_WIDTH-100,90,STANDARD_PICTURE_WIDTH,STANDARD_PICTURE_HEIGHT);
                _window->Draw(v1.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 1)
            {
                Picture v2(_graphicLibrary->getImage(5), SCREEN_WIDTH-100,90,FIREBALL_PICTURE_WIDTH,FIREBALL_PICTURE_HEIGHT);
                _window->Draw(v2.getSprite());
                
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 2)
            {
                Picture v3(_graphicLibrary->getImage(18), SCREEN_WIDTH-100,90,TINY_PICTURE_WIDTH,TINY_PICTURE_HEIGHT);
                _window->Draw(v3.getSprite());
                
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 3)
            {
                Picture v4(_graphicLibrary->getImage(23), SCREEN_WIDTH-100,90,LASER_PICTURE_WIDTH,LASER_PICTURE_HEIGHT);
                _window->Draw(v4.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 4)
            {
                Picture v5(_graphicLibrary->getImage(4), SCREEN_WIDTH-100,90,DOUBLE_TINY_LASER_PICTURE_WIDTH,DOUBLE_TINY_LASER_PICTURE_HEIGHT);
                _window->Draw(v5.getSprite());
            }
            

            
            
            #ifdef __linux__
            if(_gameModel->getLevel()->getAlly() != nullptr){
            #else
            if(_gameModel->getLevel()->getAlly() != 0){
            #endif
                int xp = _gameModel->getLevel()->getAlly()->getX();
                int yp = _gameModel->getLevel()->getAlly()->getY();
                Picture ally(_graphicLibrary->getImage(17), xp,yp,ALLY_PICTURE_WIDTH,ALLY_PICTURE_HEIGHT,0+(ALLY_PICTURE_WIDTH/3)*k3,0,(ALLY_PICTURE_WIDTH/3)+(ALLY_PICTURE_WIDTH/3)*k3,ALLY_PICTURE_HEIGHT);
                _window->Draw(ally.getSprite());
                
                Picture life(_graphicLibrary->getImage(25), 15,5,20,20);
                _window->Draw(life.getSprite());
                
                String p2("x", font , 15);
                p2.SetX(40);
                p2.SetY(5);
                p2.SetColor(Color(255, 255, 255));
                _window->Draw(p2);
                
                std::string valeurPrice;
                std::stringstream out1;
                out1 << _gameModel->getLevel()->getAlly()->getNumberOfLife();
                valeurPrice = out1.str();
                
                String textPrixe(valeurPrice, font , 15);
                textPrixe.SetX(50);
                textPrixe.SetY(5);
                textPrixe.SetColor(Color(255, 255, 255));
                _window->Draw(textPrixe);
            }
        }
        
        if(_menu->getShop())
        {//
            Picture bg(_graphicLibrary->getImage(26), 0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
            _window->Draw(bg.getSprite());
            
            
            String money("Money :", font , 20);
            money.SetX(40);
            money.SetY(30);
            money.SetColor(Color(255, 255, 255));
            _window->Draw(money);
            
            std::string valeurMoney;
            std::stringstream out1;
            out1 << _gameModel->getLevel()->getAlly()->getScore();
            valeurMoney = out1.str();
            
            String textMoney(valeurMoney, font , 20);
            textMoney.SetX(135);
            textMoney.SetY(30);
            textMoney.SetColor(Color(255, 255, 255));
            _window->Draw(textMoney);
            
            
            int rang = 1;
            
            sf::Shape Line0 = sf::Shape::Line(150, 90, 150, 100*6+90 , 1, Color(255, 255, 255));
            _window->Draw(Line0);
            
            showItems(rang, 12, "Standard ball", STANDARD_PICTURE_WIDTH, STANDARD_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
            
            sf::Shape Line1 = sf::Shape::Line(10, 100*1+90, SCREEN_WIDTH-10, 100*1+90 , 1, Color(255, 255, 255));
            _window->Draw(Line1);
            
            rang++;
            showItems(rang, 5, "Fire ball", FIREBALL_PICTURE_WIDTH, FIREBALL_PICTURE_HEIGHT, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
            
            sf::Shape Line2 = sf::Shape::Line(10, 100*2+90, SCREEN_WIDTH-10, 100*2+90 , 1, Color(255, 255, 255));
            _window->Draw(Line2);
            
            rang++;
            showItems(rang, 18, "Little laser", 9, 20, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
            
            sf::Shape Line3 = sf::Shape::Line(10, 100*3+90, SCREEN_WIDTH-10, 100*3+90 , 1, Color(255, 255, 255));
            _window->Draw(Line3);
            
            rang++;
            showItems(rang, 4, "Double laser", 17, 16, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
            
            sf::Shape Line4 = sf::Shape::Line(10, 100*4+90, SCREEN_WIDTH-10, 100*4+90 , 1, Color(255, 255, 255));
            _window->Draw(Line4);
            
            rang++;
            showItems(rang, 23, "Big laser", 8, 30, _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getPrice(), _gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getDamage());
            
            sf::Shape Line5 = sf::Shape::Line(10, 100*5+90, SCREEN_WIDTH-10, 100*5+90 , 1, Color(255, 255, 255));
            _window->Draw(Line5);
            
            Picture life(_graphicLibrary->getImage((25)), 70, 620, 20, 20);
            _window->Draw(life.getSprite());
            
            String li("New life", font , 15);
            li.SetX(45);
            li.SetY(100*6+60);
            li.SetColor(Color(255, 255, 255));
            _window->Draw(li);
            
            rang++;
            Shape c;
            c.AddPoint(450, 100*rang+10, Color(255, 255, 255), Color(255,255,255));
            c.AddPoint(550, 100*rang+10, Color(255, 255, 255), Color(255,255,255));
            c.AddPoint(550, 100*rang+30, Color(255, 255, 255), Color(255,255,255));
            c.AddPoint(450, 100*rang+30, Color(255, 255, 255), Color(255,255,255));
            
            c.EnableFill(false);
            c.EnableOutline(true);
            c.SetOutlineWidth(1);
            
            _window->Draw(c);

            String buyText("Buy", font , 15);
            buyText.SetX(490);
            buyText.SetY(100*rang+12);
            buyText.SetColor(Color(255, 255, 255));
            _window->Draw(buyText);
            
            String s2("Life : ", font , 15);
            s2.SetX(175);
            s2.SetY(100*rang+20);
            s2.SetColor(Color(255, 255, 255));
            _window->Draw(s2);
            
            std::string valeurLife;
            std::stringstream out2;
            out2 << _gameModel->getLevel()->getAlly()->getNumberOfLife();
            valeurLife = out2.str();
            
            String textPrixe(valeurLife, font , 15);
            textPrixe.SetX(270);
            textPrixe.SetY(100*rang+20);
            textPrixe.SetColor(Color(255, 255, 255));
            _window->Draw(textPrixe);
            
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

void GameViewSFML::showItems(int rang, int numPicture, string name, int width, int height, int price, int damage) const{
    Picture fireBall(_graphicLibrary->getImage((numPicture)), 60, 30+rang*100, width, height);
    _window->Draw(fireBall.getSprite());
    
    String fr(name, font , 15);
    fr.SetX(40);
    fr.SetY(100*rang+60);
    fr.SetColor(Color(255, 255, 255));
    _window->Draw(fr);
    
    String p2("Price : ", font , 15);
    p2.SetX(175);
    p2.SetY(100*rang+40);
    p2.SetColor(Color(255, 255, 255));
    _window->Draw(p2);
    
    std::string valeurPrice;
    std::stringstream out1;
    out1 << price;
    valeurPrice = out1.str();
    
    String textPrixe(valeurPrice, font , 15);
    textPrixe.SetX(270);
    textPrixe.SetY(100*rang+40);
    textPrixe.SetColor(Color(255, 255, 255));
    _window->Draw(textPrixe);
    
    
    String d2("Dommage : ", font , 15);
    d2.SetX(175);
    d2.SetY(100*rang+60);
    d2.SetColor(Color(255, 255, 255));
    _window->Draw(d2);
    
    std::string valeurDamage;
    std::stringstream out2;
    out2 << damage;
    valeurDamage = out2.str();
    
    String textDamage(valeurDamage, font , 15);
    textDamage.SetX(270);
    textDamage.SetY(100*rang+60);
    textDamage.SetColor(Color(255, 255, 255));
    _window->Draw(textDamage);
    
    String s2("State : ", font , 15);
    s2.SetX(175);
    s2.SetY(100*rang+20);
    s2.SetColor(Color(255, 255, 255));
    _window->Draw(s2);
    
    Shape buy;
    buy.AddPoint(450, 100*rang+10, Color(255, 255, 255), Color(255,255,255));
    buy.AddPoint(550, 100*rang+10, Color(255, 255, 255), Color(255,255,255));
    buy.AddPoint(550, 100*rang+30, Color(255, 255, 255), Color(255,255,255));
    buy.AddPoint(450, 100*rang+30, Color(255, 255, 255), Color(255,255,255));
    
    buy.EnableFill(false);
    buy.EnableOutline(true);
    buy.SetOutlineWidth(1);
    _window->Draw(buy);
    
    String buyText("Buy", font , 15);
    buyText.SetX(490);
    buyText.SetY(100*rang+12);
    buyText.SetColor(Color(255, 255, 255));
    _window->Draw(buyText);
    
    Shape arm;
    arm.AddPoint(450, 100*rang+50, Color(255, 255, 255), Color(255,255,255));
    arm.AddPoint(550, 100*rang+50, Color(255, 255, 255), Color(255,255,255));
    arm.AddPoint(550, 100*rang+70, Color(255, 255, 255), Color(255,255,255));
    arm.AddPoint(450, 100*rang+70, Color(255, 255, 255), Color(255,255,255));
    
    String armText("Arm", font , 15);
    armText.SetX(490);
    armText.SetY(100*rang+52);
    armText.SetColor(Color(255, 255, 255));
    _window->Draw(armText);
    
    arm.EnableFill(false);
    arm.EnableOutline(true);
    arm.SetOutlineWidth(1);
    
    _window->Draw(arm);
    
    for(int i = 0; i<5; i++){
        Shape t;
        t.AddPoint(250+25*i, rang*100+25, Color(255, 255, 255), Color(255,255,255));
        t.AddPoint(260+25*i, rang*100+25, Color(255, 255, 255), Color(255,255,255));
        t.AddPoint(260+25*i, rang*100+35, Color(255, 255, 255), Color(255,255,255));
        t.AddPoint(250+25*i, rang*100+35, Color(255, 255, 255), Color(255,255,255));
        
        t.EnableFill(false);
        t.EnableOutline(true);
        t.SetOutlineWidth(1);
        
        _window->Draw(t);
        
        if(_gameModel->getLevel()->getAlly()->getOneBulletBonus(rang-1)->getState()>i){
            t.AddPoint(250+25*i, rang*100+25, Color(0, 255, 0), Color(0,255,0));
            t.AddPoint(260+25*i, rang*100+25, Color(0, 255, 0), Color(0,255,0));
            t.AddPoint(260+25*i, rang*100+35, Color(0, 255, 0), Color(0,255,0));
            t.AddPoint(250+25*i, rang*100+35, Color(0, 255, 0), Color(0,255,0));
            
            t.EnableFill(true);
            t.EnableOutline(false);
            t.SetOutlineWidth(1);
            
            _window->Draw(t);
        }
        else{
            t.AddPoint(250+25*i, rang*100+25, Color(255, 0, 0), Color(255,0,0));
            t.AddPoint(260+25*i, rang*100+25, Color(255, 0, 0), Color(255,0,0));
            t.AddPoint(260+25*i, rang*100+35, Color(255, 0, 0), Color(255,0,0));
            t.AddPoint(250+25*i, rang*100+35, Color(255, 0, 0), Color(255,0,0));
            
            t.EnableFill(true);
            t.EnableOutline(false);
            t.SetOutlineWidth(1);
            
            _window->Draw(t);
        }
    }
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
                    if((mouseX > 450) && (mouseX < 550)){
                        int rang = 0;
                        if((mouseY>110) && (mouseY<130)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(rang)){
                                    _gameModel->getLevel()->getAlly()->setScore(_gameModel->getLevel()->getAlly()->getScore()-_gameModel->getLevel()->getAlly()->getOneBulletBonus(rang)->getPrice());
                                }
                            }
                        }
                        rang++;
                        if((mouseY>210) && (mouseY<230)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(rang)){
                                    _gameModel->getLevel()->getAlly()->setScore(_gameModel->getLevel()->getAlly()->getScore()-_gameModel->getLevel()->getAlly()->getOneBulletBonus(rang)->getPrice());
                                }
                            }
                        }
                        rang++;
                        if((mouseY>310) && (mouseY<330)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(rang)){
                                    _gameModel->getLevel()->getAlly()->setScore(_gameModel->getLevel()->getAlly()->getScore()-_gameModel->getLevel()->getAlly()->getOneBulletBonus(rang)->getPrice());
                                }
                            }
                        }
                        rang++;
                        if((mouseY>410) && (mouseY<430)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(rang)){
                                    _gameModel->getLevel()->getAlly()->setScore(_gameModel->getLevel()->getAlly()->getScore()-_gameModel->getLevel()->getAlly()->getOneBulletBonus(rang)->getPrice());
                                }
                            }
                        }
                        rang++;
                        if((mouseY>510) && (mouseY<530)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(rang)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(rang)){
                                    _gameModel->getLevel()->getAlly()->setScore(_gameModel->getLevel()->getAlly()->getScore()-_gameModel->getLevel()->getAlly()->getOneBulletBonus(rang)->getPrice());
                                }
                            }
                        }
                        if((mouseY>610) && (mouseY<630)){
                            if(_gameModel->getLevel()->getAlly()->getScore()>200 && _gameModel->getLevel()->getAlly()->getNumberOfLife()<30){
                                _gameModel->getLevel()->getAlly()->setNumberOfLife(_gameModel->getLevel()->getAlly()->getNumberOfLife() + 1);
                            }
                        }
                        
                        
                        if((mouseY>150) && (mouseY<170)){
                            _gameModel->getLevel()->getAlly()->changeBonus(0);
                        }
                        if((mouseY>250) && (mouseY<270)){
                            _gameModel->getLevel()->getAlly()->changeBonus(1);
                        }
                        if((mouseY>350) && (mouseY<370)){
                            _gameModel->getLevel()->getAlly()->changeBonus(2);
                        }
                        if((mouseY>450) && (mouseY<470)){
                            _gameModel->getLevel()->getAlly()->changeBonus(3);
                        }
                        if((mouseY>550) && (mouseY<570)){
                            _gameModel->getLevel()->getAlly()->changeBonus(4);
                        }

                        
                    }

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
