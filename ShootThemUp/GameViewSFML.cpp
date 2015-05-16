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
    
    if (!Buffer.LoadFromFile("tirJoueur.wav"))
    {
        cout << "The sound can't be load" << endl;
    }else{
        Sound.SetBuffer(Buffer);
        Sound.SetPitch(1.5f);
        Sound.SetVolume(75.f);
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
        time.Reset();
    }

    else if(_menu->getGame())
    {
        if(_menu->getLevel())
        {
            Picture bg(_graphicLibrary->getImage(0), 0,_yBackground,MODEL_WIDTH,MODEL_HEIGHT);
            Picture bg2(_graphicLibrary->getImage(0), 0,_yBackground2,MODEL_WIDTH,MODEL_HEIGHT);

            _window->Draw(bg.getSprite());
            _window->Draw(bg2.getSprite());
            
            if(_menu->getReady()){
                String ready("Are you ready?", font , 35);
                ready.SetX(MODEL_WIDTH/2-130);
                ready.SetY(MODEL_HEIGHT/2-100);
                ready.SetColor(Color(255, 255, 255));
                _window->Draw(ready);
                if(time.GetElapsedTime()<=1){
                    String three("3", font , 70);
                    three.SetX(MODEL_WIDTH/2-18);
                    three.SetY(MODEL_HEIGHT/2-35);
                    three.SetColor(Color(255, 255, 255));
                    _window->Draw(three);

                }
                else if(time.GetElapsedTime()<=2){
                    String two("2", font , 70);
                    two.SetX(MODEL_WIDTH/2-18);
                    two.SetY(MODEL_HEIGHT/2-35);
                    two.SetColor(Color(255, 255, 255));
                    _window->Draw(two);
                }
                else if(time.GetElapsedTime()<=3){
                    String one("1", font , 70);
                    one.SetX(MODEL_WIDTH/2-18);
                    one.SetY(MODEL_HEIGHT/2-35);
                    one.SetColor(Color(255, 255, 255));
                    _window->Draw(one);
                }
                else if (time.GetElapsedTime()<=4){
                    String go("Go!", font , 70);
                    go.SetX(MODEL_WIDTH/2-50);
                    go.SetY(MODEL_HEIGHT/2-35);
                    go.SetColor(Color(255, 255, 255));
                    _window->Draw(go);
                }
                else{
                    _menu->setReady(false);
                }
            }
            else{
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
                        vieBoss.AddPoint(xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / ((float)BOSS_LIFE + (_gameModel->getLevel()->getLevelNumber()-1) *50)) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb-15, Color(240, 76, 36), Color(240, 76, 36));
                        vieBoss.AddPoint(xb + (((float)_gameModel->getLevel()->getBoss()->getHealth() / ((float)BOSS_LIFE + (_gameModel->getLevel()->getLevelNumber()-1) *50)) * (float)_gameModel->getLevel()->getBoss()->getWidth()), yb-10, Color(240, 76, 36), Color(240, 76, 36));
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
                Picture ally(_graphicLibrary->getImage(17), xp,yp,ALLY_PICTURE_WIDTH,ALLY_PICTURE_HEIGHT,0+(ALLY_PICTURE_WIDTH/3)*(_gameModel->getNumberTour()%3),0,(ALLY_PICTURE_WIDTH/3)+(ALLY_PICTURE_WIDTH/3)*(_gameModel->getNumberTour()%3),ALLY_PICTURE_HEIGHT);
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
            
            Shape cadreNoir;
            cadreNoir.AddPoint(MODEL_WIDTH, 0,  Color(0, 0, 0), Color(0, 0, 0));
            cadreNoir.AddPoint(SCREEN_WIDTH, 0, Color(0, 0, 0), Color(0, 0, 0));
            cadreNoir.AddPoint(SCREEN_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0), Color(0, 0, 0));
            cadreNoir.AddPoint(MODEL_WIDTH, SCREEN_HEIGHT, Color(0, 0, 0), Color(0, 0, 0));
                
            cadreNoir.EnableFill(true);
            _window->Draw(cadreNoir);

            //
            String textScore("SCORE : ", font , 15);
            textScore.SetX(SCREEN_WIDTH - 180);
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
            String textLevel("WAVE : ", font , 15);
            textLevel.SetX(SCREEN_WIDTH - 180);
            textLevel.SetY(25);
            textLevel.SetColor(Color(255, 255, 255));
            _window->Draw(textLevel);
                
            std::string valeurNiveau;
            std::stringstream out2;
            out2 << _gameModel->getLevel()->getLevelNumber();
            valeurNiveau = out2.str();
                
            String valeurLevel(valeurNiveau, font , 15);
            valeurLevel.SetX(SCREEN_WIDTH - 70);
            valeurLevel.SetY(25);
            valeurLevel.SetColor(Color(255, 255, 255));
            _window->Draw(valeurLevel);
                
            //
            String textEnemies("ENNEMIES : ", font , 15);
            textEnemies.SetX(SCREEN_WIDTH - 180);
            textEnemies.SetY(45);
            textEnemies.SetColor(Color(255, 255, 255));
            _window->Draw(textEnemies);
                
            std::string valeurEnemies;
            std::stringstream out3;
            out3 << _gameModel->getLevel()->getNumberOfEnemies();
            valeurEnemies = out3.str();
        
            String valeurTextEnemies(valeurEnemies, font , 15);
            valeurTextEnemies.SetX(SCREEN_WIDTH - 70);
            valeurTextEnemies.SetY(45);
            valeurTextEnemies.SetColor(Color(255, 255, 255));
            _window->Draw(valeurTextEnemies);
                
            //
            String textMain("MAIN SHOOT", font , 15);
            textMain.SetX(SCREEN_WIDTH - 135);
            textMain.SetY(100);
            textMain.SetColor(Color(255, 255, 255));
            _window->Draw(textMain);
                
            String textPowerMain("POWER : ", font , 15);
            textPowerMain.SetX(SCREEN_WIDTH - 180);
            textPowerMain.SetY(130);
            textPowerMain.SetColor(Color(255, 255, 255));
            _window->Draw(textPowerMain);
                
            std::string valeurPoweMain;
            std::stringstream out5;
            out5 << _gameModel->getLevel()->getAlly()->getOneBulletBonus(_gameModel->getLevel()->getAlly()->getMainBulletType())->getDamage();
            valeurPoweMain = out5.str();
                
            String textValeurPowerMain(valeurPoweMain, font , 15);
            textValeurPowerMain.SetX(SCREEN_WIDTH - 70);
            textValeurPowerMain.SetY(130);
            textValeurPowerMain.SetColor(Color(255, 255, 255));
            _window->Draw(textValeurPowerMain);
                
            if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 0)
            {
                Picture v1(_graphicLibrary->getImage(12), SCREEN_WIDTH-100,170,STANDARD_PICTURE_WIDTH,STANDARD_PICTURE_HEIGHT);
                _window->Draw(v1.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 1)
            {
                Picture v2(_graphicLibrary->getImage(5), SCREEN_WIDTH-100,170,FIREBALL_PICTURE_WIDTH,FIREBALL_PICTURE_HEIGHT);
                _window->Draw(v2.getSprite());
                
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 2)
            {
                Picture v3(_graphicLibrary->getImage(18), SCREEN_WIDTH-100,170,TINYLASER_PICTURE_WIDTH,TINYLASER_PICTURE_HEIGHT);
                _window->Draw(v3.getSprite());
                
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 3)
            {
                Picture v4(_graphicLibrary->getImage(23), SCREEN_WIDTH-100,170,LASER_PICTURE_WIDTH,LASER_PICTURE_HEIGHT);
                _window->Draw(v4.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getMainBulletType() == 4)
            {
                Picture v5(_graphicLibrary->getImage(4), SCREEN_WIDTH-100,170,DOUBLE_TINY_LASER_PICTURE_WIDTH,DOUBLE_TINY_LASER_PICTURE_HEIGHT);
                _window->Draw(v5.getSprite());
            }
                
                
            String textBonus("BONUS SHOOT", font , 15);
            textBonus.SetX(SCREEN_WIDTH - 135);
            textBonus.SetY(220);
            textBonus.SetColor(Color(255, 255, 255));
            _window->Draw(textBonus);
                
            String textPower("POWER : ", font , 15);
            textPower.SetX(SCREEN_WIDTH - 180);
            textPower.SetY(245);
            textPower.SetColor(Color(255, 255, 255));
            _window->Draw(textPower);
                
            std::string valeurPower;
            std::stringstream out6;
            out6 << _gameModel->getLevel()->getAlly()->getBulletBonus()->getDamage();
            valeurPower = out6.str();
                
            String textValeurPower(valeurPower, font , 15);
            textValeurPower.SetX(SCREEN_WIDTH - 70);
            textValeurPower.SetY(245);
            textValeurPower.SetColor(Color(255, 255, 255));
            _window->Draw(textValeurPower);
                
            String textNumberBonus("NUMBER : ", font , 15);
            textNumberBonus.SetX(SCREEN_WIDTH - 180);
            textNumberBonus.SetY(265);
            textNumberBonus.SetColor(Color(255, 255, 255));
            _window->Draw(textNumberBonus);
                
            std::string valeurNumberBonusShoot;
            std::stringstream out4;
            out4 << _gameModel->getLevel()->getAlly()->getNumberShootBonusMax()-_gameModel->getLevel()->getAlly()->getNumberShootBonus();
            valeurNumberBonusShoot = out4.str();
                
            String textNumberBonusShoot(valeurNumberBonusShoot, font , 15);
            textNumberBonusShoot.SetX(SCREEN_WIDTH - 70);
            textNumberBonusShoot.SetY(265);
            textNumberBonusShoot.SetColor(Color(255, 255, 255));
            _window->Draw(textNumberBonusShoot);
                
            
            if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 0)
            {
                Picture v1(_graphicLibrary->getImage(12), SCREEN_WIDTH-100,305,STANDARD_PICTURE_WIDTH,STANDARD_PICTURE_HEIGHT);
                _window->Draw(v1.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 1)
            {
                Picture v2(_graphicLibrary->getImage(5), SCREEN_WIDTH-100,305,FIREBALL_PICTURE_WIDTH,FIREBALL_PICTURE_HEIGHT);
                _window->Draw(v2.getSprite());
                    
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 2)
            {
                Picture v3(_graphicLibrary->getImage(18), SCREEN_WIDTH-100,305,TINYLASER_PICTURE_WIDTH,TINYLASER_PICTURE_HEIGHT);
                _window->Draw(v3.getSprite());
                
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 3)
            {
                Picture v4(_graphicLibrary->getImage(23), SCREEN_WIDTH-100,305,LASER_PICTURE_WIDTH,LASER_PICTURE_HEIGHT);
                _window->Draw(v4.getSprite());
            }
            else if(_gameModel->getLevel()->getAlly()->getBulletBonusType() == 4)
            {
                Picture v5(_graphicLibrary->getImage(4), SCREEN_WIDTH-100,305,DOUBLE_TINY_LASER_PICTURE_WIDTH,DOUBLE_TINY_LASER_PICTURE_HEIGHT);
                _window->Draw(v5.getSprite());
            }
            
            sf::Shape Line1 = sf::Shape::Line(MODEL_WIDTH, 0, MODEL_WIDTH, MODEL_HEIGHT , 1, Color(255, 255, 255));
            _window->Draw(Line1);
                
            for(int i = 0; i<10; i++){
                if(i%2==0){
                    sf::Shape Line1 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 85, MODEL_WIDTH+20*i+20+10, 85 , 1, Color(255, 255, 255));
                    _window->Draw(Line1);
                        
                    sf::Shape Line2 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 205, MODEL_WIDTH+20*i+20+10, 205 , 1, Color(255, 255, 255));
                    _window->Draw(Line2);
                    
                    sf::Shape Line3 = sf::Shape::Line(MODEL_WIDTH+20*i+10, 355, MODEL_WIDTH+20*i+20+10, 355 , 1, Color(255, 255, 255));
                    _window->Draw(Line3);
                }
            }
        }
        
            
            
        if(_menu->getShop())
        {//
            Picture bg(_graphicLibrary->getImage(26), 0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
            _window->Draw(bg.getSprite());
            
            
            String money("Money :", font , 20);
            money.SetX(15);
            money.SetY(30);
            money.SetColor(Color(255, 255, 255));
            _window->Draw(money);
            
            std::string valeurMoney;
            std::stringstream out1;
            out1 << _gameModel->getLevel()->getAlly()->getScore();
            valeurMoney = out1.str();
            
            String textMoney(valeurMoney, font , 20);
            textMoney.SetX(115);
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
            
            String p2("Price : ", font , 15);
            p2.SetX(175);
            p2.SetY(100*rang+40);
            p2.SetColor(Color(255, 255, 255));
            _window->Draw(p2);
            
            std::string valeurLifePrice;
            std::stringstream out3;
            out3 << ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100;
            valeurLifePrice = out3.str();
            
            String textLifePrice(valeurLifePrice, font , 15);
            textLifePrice.SetX(270);
            textLifePrice.SetY(640);
            textLifePrice.SetColor(Color(255, 255, 255));
            _window->Draw(textLifePrice);
            
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
        else if(_menu->getSaveScore()){
            Shape cadreFinLevel;
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-50, Color(255, 255, 255), Color(255,255,255));
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2+75, SCREEN_HEIGHT-50, Color(255, 255, 255), Color(255,255,255));
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2+75, SCREEN_HEIGHT-20, Color(255, 255, 255), Color(255,255,255));
            cadreFinLevel.AddPoint(SCREEN_WIDTH/2-75, SCREEN_HEIGHT-20, Color(255, 255, 255), Color(255,255,255));
            
            cadreFinLevel.EnableFill(false);
            cadreFinLevel.EnableOutline(true);
            cadreFinLevel.SetOutlineWidth(2);
            
            _window->Draw(cadreFinLevel);
            
            String nextLevel("Confirm", font , 20);
            nextLevel.SetX(SCREEN_WIDTH/2-60);
            nextLevel.SetY(SCREEN_HEIGHT-45);
            nextLevel.SetColor(Color(255, 255, 255));
            _window->Draw(nextLevel);
        }
    }

    else if(_menu->getScore()){

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
    fr.SetX(25);
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
    
    String buyText("Improve", font , 15);
    buyText.SetX(470);
    buyText.SetY(100*rang+12);
    buyText.SetColor(Color(255, 255, 255));
    _window->Draw(buyText);
    
    Shape arm;
    arm.AddPoint(450, 100*rang+50, Color(255, 255, 255), Color(255,255,255));
    arm.AddPoint(550, 100*rang+50, Color(255, 255, 255), Color(255,255,255));
    arm.AddPoint(550, 100*rang+70, Color(255, 255, 255), Color(255,255,255));
    arm.AddPoint(450, 100*rang+70, Color(255, 255, 255), Color(255,255,255));
    
    String armText("Arm", font , 15);
    armText.SetX(488);
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
                    _menu->setReady(true);
                    _menu->setLevel(true);
                    _menu->setMenu(false);
                    time.Reset();
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
            if(_menu->getLevel() && !_menu->getReady())
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
                        Sound.Play();
                        shoot.Reset();
                    }
                }
                if(input.IsKeyDown(Key::V)){
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
                        if((mouseY>110) && (mouseY<130)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(0)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(0)){
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(0)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(0)->growPrice();
                                }
                            }
                        }
                        if((mouseY>210) && (mouseY<230)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(1)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(1)){
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(1)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(1)->growPrice();
                                }
                            }
                        }
                        if((mouseY>310) && (mouseY<330)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(2)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(2)){
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(2)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(2)->growPrice();
                                }
                            }
                        }
                        if((mouseY>410) && (mouseY<430)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(3)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(3)){
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(3)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(3)->growPrice();
                                }
                            }
                        }
                        if((mouseY>510) && (mouseY<530)){
                            if(_gameModel->getLevel()->getAlly()->canBuyItem(4)){
                                if(_gameModel->getLevel()->getAlly()->improveOneBulletBonus(4)){
                                    _gameModel->getLevel()->getAlly()->reduceScore(_gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->getPrice());
                                    _gameModel->getLevel()->getAlly()->getOneBulletBonus(4)->growPrice();
                                }
                            }
                        }
                        if((mouseY>610) && (mouseY<630)){
                            if(_gameModel->getLevel()->getAlly()->getScore() > ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100 && _gameModel->getLevel()->getAlly()->getNumberOfLife()<5){
                                _gameModel->getLevel()->getAlly()->setNumberOfLife(_gameModel->getLevel()->getAlly()->getNumberOfLife() + 1);
                                _gameModel->getLevel()->getAlly()->reduceScore(ADD_LIFE_PRICE + _gameModel->getLevel()->getAlly()->getNumberLifeBuy() * 100);
                                _gameModel->getLevel()->getAlly()->setNumberLifeBuy(_gameModel->getLevel()->getAlly()->getNumberLifeBuy() + 1);
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
                        time.Reset();
                        _menu->setReady(true);
                        _menu->setLevel(true);
                        _menu->setShop(false);
                    }
                }
            }
        }

        else if(_menu->getSaveScore())
        {
            if(input.IsMouseButtonDown(Mouse::Left) || input.IsKeyDown(Key::Return)){
                //if((mouseX > 450) && (mouseX < 550)){
                if(((mouseX > SCREEN_WIDTH/2-75) && (mouseX < SCREEN_WIDTH/2+75) && (mouseY > SCREEN_HEIGHT-50 ) &&  (mouseY < SCREEN_HEIGHT+20)) || input.IsKeyDown(Key::Return))
                {
                    _menu->setMenu(true);
                    _menu->setSaveScore(false);
                    _menu->setReady(true);
                    _menu->setLevel(true);
                    _menu->setShop(false);
                }
            }
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
