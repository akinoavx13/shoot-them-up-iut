//
//  Level.h
//  ShootThemUp
//
//  Created by Nicolas Valaise on 18/03/2015.
//  Copyright (c) 2015 Nicolas Valaise. All rights reserved.
//

#include "Level.h"

using namespace std;

/*
 * default constructor
 */
Level::Level() : _levelNumber(DEFAULT_LEVEL_NUMBER), _nbEnemies(DEFAULT_LEVEL_ENEMY_NUMBER){
    
    int x = 0;
    int y = 100;
    
    for(int i = 0; i<_nbEnemies; i++){
        x += DEFAULT_LEVEL_INITIAL_ENEMY_OFFSET;
        if(x >= MODEL_WIDTH){
            y += DEFAULT_LEVEL_INITIAL_ENEMY_OFFSET;
        }
        
        Enemy* enemy = new Enemy(x, y, 100);
        enemy->setLevel(this);
        _tabEnemies.push_back(enemy);
    }
    
    _ally = new Ally();
    _ally->setLevel(this);
    
    _boss = nullptr;
}

/*
 * destructor
 * info : virtual
 */
Level::~Level(){
    
    for (auto p : _tabEnemies) {
        delete p;
    }
    
    for (auto p : _tabBullets) {
        delete p;
    }
    
    if(_ally !=  nullptr){
        delete _ally;
    }
    if(_boss !=  nullptr){
        delete _boss;
    }
    
}

//----------METHODS----------
/*
 * returns : true if the level is finish.
 * info : constant
 */
bool Level::isFinish() const{
    
    return _ally->isOver();
    
}

/*
 * returns : string of enemy's toString
 * info : constant
 */
string Level::toString() const{
    string str;
    
    for(auto p : _tabEnemies){
        str += p->toString();
    }
    
    return str;
}

/*
 * check for all graphic element in the level if there are collision between them
 */
void Level::checkCollisions(){
    
    bool collision = false;
    
    //collision between ally and bullets
    int a = 0;
    for (auto bullet : _tabBullets) {
        if(_ally->collisions(bullet)){
            cout << "Vous avez pris une balle !" << endl;
            _ally->setHealth(_ally->getHealth() - bullet->getDamage());
            collision = true;
            
            if(_ally->isDead()){
                cout << "Vous etes mort" << endl;
            }
            
            _tabBullets.erase(_tabBullets.begin() + a);
            delete bullet;
        }
        a++;
    }
    
    //collision between boss and bullets
    int b = 0;
    for (auto bullet : _tabBullets) {
        if(_boss->collisions(bullet)){
            cout << "Un boss à pris une balle !" << endl;
            _boss->setHealth(_boss->getHealth() - bullet->getDamage());
            collision = true;
            
            if(_boss->isDead()){
                cout << "Vous avez tué le boss" << endl;
                delete _boss;
            }
            
            _tabBullets.erase(_tabBullets.begin() + b);
            delete bullet;
        }
        b++;
    }
    
    //collision between enemies and bullets
    int i = 0;
    int j = 0;
    for (auto enemy : _tabEnemies) {
        for(auto bullet : _tabBullets){
            if(enemy->collisions(bullet)){
                cout << "Un ennemi a pris une balle !" << endl;
                enemy->setHealth(enemy->getHealth() - bullet->getDamage());
                collision = true;
                
                _tabBullets.erase(_tabBullets.begin() + i);
                delete bullet;
                
                _ally->setPoint(_levelNumber*2);
                
                if(enemy->isDead()){
                    cout << "Vous avez tué un ennemi" << endl;
                    _tabEnemies.erase(_tabEnemies.begin() + j);
                    delete enemy;
                }
            }
            i++;
        }
        j++;
    }
    
    //collision between ally and enemies
    int k = 0;
    for (auto enemy : _tabEnemies) {
        if(_ally->collisions(enemy)){
            
            _ally->setHealth(_ally->getHealth() - (_ally->getHealth() / 4));
            
            _tabEnemies.erase(_tabEnemies.begin() + k);
            delete enemy;
        }
        k++;
    }
    
    //collision between ally and boss
    
    if(_ally->collisions(_boss)){
        
        _ally->setHealth(_ally->getHealth() - (_ally->getHealth() / 4));
        _boss->setHealth(_boss->getHealth() - (_boss->getHealth() / 4));
        if(_boss->isDead()){
            cout << "Vous avez tué un ennemi" << endl;
            delete _boss;
        }
    }
    
    
    if(!collision){
        cout << "Aucune collision pour le moment" << endl;
    }
    
    //uniquement pour le model, sinon pour la vue, c'est que la fonction qui verifie si la balle et encore dans la fenetre
    for(auto bullet : _tabBullets){
        delete bullet;
    }
    _tabBullets.clear();
    
    
    //pour détruire la balle quand elle est hors du cadre, utilisé pour la vue
    /*
     for(auto bullet : _tabBullets){
     if((bullet->getX() >= MODEL_WIDTH && bullet->getX() <= 0) || (bullet->getY() >= MODEL_HEIGHT && bullet->getX()<= 0)){
     delete bullet;
     }
     }
     */
}

/*
 * add a bullet in the bullet's vector
 * params : bullet
 */
void Level::addBullet(Bullet* bullet){
    _tabBullets.push_back(bullet);
}

/*
 * move enemies in the level
 * info : constant
 */
void Level::moveEnemies() const{
    int x;
    int y = 100;
    
    srand((unsigned int)time(NULL));
    
    for (auto enemy : _tabEnemies) {
        x = rand() % 501;
        enemy->move(x, y);
    }
    
}

/*
 * allows all enemies shoot
 * info : constant
 */
void Level::EnemiesShoot() const{
    
    for (auto enemy : _tabEnemies) {
        enemy->shoot();
    }
    
}

void Level::addBoss(){
    if(_boss == nullptr){
        _boss = new Boss(100, 100, 200);
        _boss->setLevel(this);
    }
}

//----------GETTERS----------
/*
 * returns : ally
 * info : constant
 */
Ally* Level::getAlly() const{
    return _ally;
}

Boss* Level::getBoss() const{
    return _boss;
}

/*
 * returns : enemies who are still in live
 * info : constant
 */
int Level::getEnemiesNumber() const{
    return (int)_tabEnemies.size();
}





















