//
//  Level.h
//  ShootThemUp
//
//  Created by Nicolas Valaise on 18/03/2015.
//  Copyright (c) 2015 Nicolas Valaise. All rights reserved.
//

#include "Level.h"
#include "const.h"

using namespace std;

/*
 * default constructor
 */
Level::Level() : _levelNumber(LEVEL_NUMBER), _nbEnemies(LEVEL_ENEMY_NUMBER){

    addEnemies();

    _ally = new Ally();
    _ally->setLevel(this);

    #ifdef __linux__
    _boss = nullptr;
    #else
    _boss = 0;
    #endif
}

/*
 * destructor
 * info : virtual
 */
Level::~Level(){

    for (int i = 0; i < _tabEnemies.size(); i++) {
        delete _tabEnemies[i];
    }
    _tabEnemies.clear();

    for (int i = 0; i < _tabBullets.size(); i++) {
        delete _tabBullets[i];
    }
    _tabBullets.clear();

    delete _ally;

    delete _boss;

}

//----------METHODS----------
/*
 * returns : true if the level is finish.
 * info : constant
 */
bool Level::isFinish() const{

    #ifdef __linux__
    return _tabEnemies.size() <= 0 && _boss == nullptr;
    #else
    return _tabEnemies.size() <= 0 && _boss == 0;
    #endif
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
    
    for (int i = 0; i < _tabBullets.size(); i++) {
        for (int j = 0; j < _tabBullets.size(); j++) {
            if(i!=j){
                if(_tabBullets[i]->collisions(_tabBullets[j])){
                    delete _tabBullets[i];
                    delete _tabBullets[j];
                    _tabBullets.erase(_tabBullets.begin() + i);
                    if(i>j)
                        _tabBullets.erase(_tabBullets.begin() + j);
                    else
                        _tabBullets.erase(_tabBullets.begin() + j-1);
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < _tabBullets.size(); i++) {
        if(_ally->collisions(_tabBullets[i])){
            int allyLife = _ally->getHealth();
            int bulletDamage = _tabBullets[i]->getDamage();
            _ally->setHealth(allyLife - bulletDamage);
            delete _tabBullets[i];
            _tabBullets.erase(_tabBullets.begin() + i);
        }
    }
    
#ifdef __linux__
    if(_boss != nullptr){
#else
    if(_boss != 0){
#endif
        if(_ally->collisions(_boss)){
            int allyLife = _ally->getHealth();
            int bossLife = _boss->getHealth();
            _ally->setHealth(allyLife - 10);
            _boss->setHealth(bossLife - 10);
            
        }
    }
    
    for (auto enemy : _tabEnemies) {
        if (_ally->collisions(enemy)) {
            int allyLife = _ally->getHealth();
            int enemyLife = enemy->getHealth();
            _ally->setHealth(allyLife - 10);
            enemy->setHealth(enemyLife - 10);
        }
    }
    
    for (int i = 0; i < _tabEnemies.size(); i++) {
        for (int j = 0; j < _tabBullets.size(); j++) {
            if(_tabEnemies[i]->collisions(_tabBullets[j])){
                if(_tabBullets[j]->getOwner() == "ally"){
                    int enemyLife = _tabEnemies[i]->getHealth();
                    int bulletDamage = _tabBullets[j]->getDamage();
                    _tabEnemies[i]->setHealth(enemyLife - bulletDamage);
                    delete _tabBullets[j];
                    _tabBullets.erase(_tabBullets.begin() + j);
                }
            }
        }
    }
#ifdef __linux__
    if(_boss != nullptr){
#else
    if(_boss != 0){
#endif
        for (int i = 0; i < _tabBullets.size(); i++) {
            if(_boss->collisions(_tabBullets[i])){
                int bossLife = _boss->getHealth();
                int bulletDamage = _tabBullets[i]->getDamage();
                _boss->setHealth(bossLife - bulletDamage);
                delete _tabBullets[i];
                _tabBullets.erase(_tabBullets.begin() + i);
            }
        }
    }

    for (int i = 0; i < _tabBullets.size(); i++) {
        if((_tabBullets[i]->getX() <= 0) ||
           (_tabBullets[i]->getX() + _tabBullets[i]->getWidth() >= MODEL_WIDTH) ||
           (_tabBullets[i]->getY() <= 0) ||
           (_tabBullets[i]->getY() + _tabBullets[i]->getHeight() >= MODEL_HEIGHT))
        {
            delete _tabBullets[i];
            _tabBullets.erase(_tabBullets.begin() + i);
        }
    }
    
    for (int i = 0; i < _tabEnemies.size(); i++) {
        if(_tabEnemies[i]->isDead()){
            _ally->setScore(_ally->getScore() + _levelNumber * 10);
            delete _tabEnemies[i];
            _tabEnemies.erase(_tabEnemies.begin() + i);
        }
    }
#ifdef __linux__
    if(_boss != nullptr && _boss->isDead()){
#else
    if(_boss != 0 && _boss->isDead()){
#endif
        _boss->move(_boss->getX(), -200);
#ifdef __linux__
        _boss = nullptr;
#else
        _boss = 0;
#endif
        _ally->setScore(_ally->getScore() + _levelNumber * 20);
    }
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
void Level::moveEnemies(float t){
    for (int i = 0; i < _tabEnemies.size(); i++) {
        if(_tabEnemies[i]->getY() > MODEL_HEIGHT || _tabEnemies[i]->getX() + _tabEnemies[i]->getWidth() <= 0 || _tabEnemies[i]->getX() >= MODEL_WIDTH){
            delete _tabEnemies[i];
            _tabEnemies.erase(_tabEnemies.begin() + i);
        }else{
            
            if(_tabEnemies[i]->getType() == 1){
                float x = sin(t) * 5 + _tabEnemies[i]->getX();
                float y = _tabEnemies[i]->getY();
                _tabEnemies[i]->move(x, y + _tabEnemies[i]->getSpeedY());
            }
            else if (_tabEnemies[i]->getType() == 2){
                float x = _tabEnemies[i]->getX();
                float y = _tabEnemies[i]->getY();
                _tabEnemies[i]->move(x, y + _tabEnemies[i]->getSpeedY());
                
            }else if(_tabEnemies[i]->getType() == 3){
                float x = sin(t/3)*2 + _tabEnemies[i]->getX();
                float y = _tabEnemies[i]->getY();
                _tabEnemies[i]->move(x, y + _tabEnemies[i]->getSpeedY());
                
            }
        }
    }
}

/*
 * allows all enemies shoot
 * info : constant
 */
void Level::EnemiesShoot() const{
    for (auto enemy : _tabEnemies) {
        float enemyX = enemy->getX();
        float enemyY = enemy->getY();
        int enemyWidth = enemy->getWidth();
        int enemyHeight = enemy->getHeight();
        if(enemyX > 0 && enemyX + enemyWidth < MODEL_WIDTH && enemyY + enemyHeight > 0 && enemyY + enemyHeight < MODEL_HEIGHT)
        enemy->shoot();
    }
}

void Level::addBoss(){
    _boss = new Boss(MODEL_WIDTH / 2 - BOSS_PICTURE_WIDTH / 2 * 3, -200, BOSS_LIFE, BOSS_FIRERATE);
    _boss->setLevel(this);
}

void Level::addEnemies(){

    srand((unsigned int)time(NULL));

    
    for(int i = 0; i < _nbEnemies; i++){
        int type = rand()%3;
        if(type == 0){
            
            float x = rand()%(MODEL_WIDTH - MIGHTY_PICTURE_WIDTH);
            float y = i * - 100;
            
            Enemy* enemy = Enemy::Mighty(x, y);
            
            enemy->setLevel(this);
            _tabEnemies.push_back(enemy);

        }
        else if (type == 1){
            float x = rand()%(MODEL_WIDTH - SUBMARINE_PICTURE_WIDTH);
            float y = i * - 200;
            
            Enemy* enemy = Enemy::Submarine(x, y);
            
            enemy->setLevel(this);
            _tabEnemies.push_back(enemy);

        }
        else if (type == 2){
            float x = rand() % (MODEL_WIDTH - TINY_PICTURE_WIDTH);
            float y = i * - 100;
            
            Enemy* enemy = Enemy::Tiny(x, y);
            
            enemy->setLevel(this);
            _tabEnemies.push_back(enemy);
        }
    }
}

void Level::deleteAllEnemy(){

    for (int i = 0; i < _tabEnemies.size(); i++) {
        delete _tabEnemies[i];
    }

    _tabEnemies.clear();

}

void Level::deleteAllBullets(){
    
    for (int i = 0; i < _tabBullets.size(); i++) {
        delete _tabBullets[i];
    }
    
    _tabBullets.clear();
    
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
vector<Enemy*> Level::getEnemies() const{
    return _tabEnemies;
}

vector<Bullet*> Level::getBullets() const{
    return _tabBullets;
}

/*
 * returns : enemies who are still in live
 * info : constant
 */
int Level::getEnemiesNumber() const{
    return (int)_tabEnemies.size();
}

int Level::getNbEnemies() const{
    return _nbEnemies;
}

int Level::getLevelNumber() const{
    return _levelNumber;
}

void Level::setNbEnemies(int nbEnemies){
    _nbEnemies = nbEnemies;
}

void Level::setLevelNumber(int levelNumber){
    _levelNumber = levelNumber;
}

int Level::getNumberOfBullets() const{
    return (int)_tabBullets.size();
}

int Level::getNumberOfEnemies() const{
    return (int)_tabEnemies.size();
}

void Level::moveBullets(){
    for(auto bullet : _tabBullets){
        float bulletX = bullet->getX();
        float bulletY = bullet->getY();
        int bulletWidth = bullet->getWidth();
        int bulletHeight = bullet->getHeight();
        int bulletSpeedX = bullet->getSpeedX();
        int bulletSpeedY = bullet->getSpeedY();
        
        if(bulletX > 0 && bulletX + bulletWidth < MODEL_WIDTH && bulletY + bulletHeight > 0 && bulletY + bulletHeight < MODEL_HEIGHT){
            bullet->move(bulletX + bulletSpeedX, bulletY + bulletSpeedY);
        }
    }
}











