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
 * CONWTRUCTOR
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
 * DESTRUCTOR
 */
Level::~Level(){

    //delete all thing in the field
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

/*
 * METHODS
 */
//return true if they are 0 enemy and no boss
bool Level::isFinish() const{

#ifdef __linux__
    return _tabEnemies.size() <= 0 && _boss == nullptr;
#else
    return _tabEnemies.size() <= 0 && _boss == 0;
#endif
}

//write some informations about the level
string Level::toString() const{
    string str;

    for(auto p : _tabEnemies){
        str += p->toString();
    }

    return str;
}

//the main function to check all collision
void Level::checkCollisions(){
    
    //bullets and bullets
    for (int i = 0; i < _tabBullets.size(); i++) {
        for (int j = 0; j < _tabBullets.size(); j++) {
            // don't select the same bullet
            if(i!=j){
                //if they is a collision, we delete them and erase them from the vector
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
    
    //bullets and player
    for (int i = 0; i < _tabBullets.size(); i++) {
        //collision detected
        if(_ally->collisions(_tabBullets[i])){
            int allyLife = _ally->getHealth();
            int bulletDamage = _tabBullets[i]->getDamage();
            
            //set player life,  delete and erase bullet
            _ally->setHealth(allyLife - bulletDamage);
            delete _tabBullets[i];
            _tabBullets.erase(_tabBullets.begin() + i);
        }
    }
    
    //the boss and the player
    //we must check if the boss exist with nullptr or 0
#ifdef __linux__
    if(_boss != nullptr){
#else
    if(_boss != 0){
#endif
        //collision detected
        if(_ally->collisions(_boss)){
            int allyLife = _ally->getHealth();
            int bossLife = _boss->getHealth();
            
            //take off life from boss and player
            _ally->setHealth(allyLife - 10);
            _boss->setHealth(bossLife - 10);
            
        }
    }
    
    //enemies and players is the same that boss and players
    for (auto enemy : _tabEnemies) {
        if (_ally->collisions(enemy)) {
            int allyLife = _ally->getHealth();
            int enemyLife = enemy->getHealth();
            _ally->setHealth(allyLife - 10);
            enemy->setHealth(enemyLife - 10);
        }
    }
    
    //bullets and enemies
    for (int i = 0; i < _tabEnemies.size(); i++) {
        for (int j = 0; j < _tabBullets.size(); j++) {
            //collision detected
            if(_tabEnemies[i]->collisions(_tabBullets[j])){
                //we take off some health point to enemy only if the shooter is the player, else we do nothing
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
    
    //boss and bullets
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

    //if bullet are outside of the screen we delete and erase them
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
    
    //if an enemy is dead we delete and erase it
    for (int i = 0; i < _tabEnemies.size(); i++) {
        if(_tabEnemies[i]->isDead()){
            _ally->setScore(_ally->getScore() + _levelNumber * 10);
            delete _tabEnemies[i];
            _tabEnemies.erase(_tabEnemies.begin() + i);
        }
    }
    
    //if the boss is dead, we move it to y = -200.
    //bullet can't touched it
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

//add bullet to the level
void Level::addBullet(Bullet* bullet){
    _tabBullets.push_back(bullet);
}

//move all the enemies
void Level::moveEnemies(float t){
    for (int i = 0; i < _tabEnemies.size(); i++) {
        //if an enemy is outside of the screen, we delete and erase it
        if(_tabEnemies[i]->getY() > MODEL_HEIGHT || _tabEnemies[i]->getX() + _tabEnemies[i]->getWidth() <= 0 || _tabEnemies[i]->getX() >= MODEL_WIDTH){
            delete _tabEnemies[i];
            _tabEnemies.erase(_tabEnemies.begin() + i);
        }else{
            //else we mve it differently in function of his type
            if(_tabEnemies[i]->getType() == 1){
                //small sinusoidale
                float x = sin(t) * 5 + _tabEnemies[i]->getX();
                float y = _tabEnemies[i]->getY();
                _tabEnemies[i]->move(x, y + _tabEnemies[i]->getSpeedY());
            }
            else if (_tabEnemies[i]->getType() == 2){
                //straight ahead
                float x = _tabEnemies[i]->getX();
                float y = _tabEnemies[i]->getY();
                _tabEnemies[i]->move(x, y + _tabEnemies[i]->getSpeedY());
                
            }else if(_tabEnemies[i]->getType() == 3){
                //bigger sinusoidale
                float x = sin(t/3)*2 + _tabEnemies[i]->getX();
                float y = _tabEnemies[i]->getY();
                _tabEnemies[i]->move(x, y + _tabEnemies[i]->getSpeedY());
            }
        }
    }
}

//all enemy shoot
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

//add the boss to the level
void Level::addBoss(){
    _boss = new Boss(MODEL_WIDTH / 2 - BOSS_PICTURE_WIDTH / 2 * 3, -200, BOSS_LIFE, BOSS_FIRERATE);
    _boss->setLevel(this);
}

//add enemies at the begening of a level
void Level::addEnemies(){

    srand((unsigned int)time(NULL));
    
    for(int i = 0; i < _nbEnemies; i++){
        int type = rand() % 3;
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

//delete all enemy of the level
void Level::deleteAllEnemy(){

    for (int i = 0; i < _tabEnemies.size(); i++) {
        delete _tabEnemies[i];
    }

    _tabEnemies.clear();

}

//delete all the bullets of the level
void Level::deleteAllBullets(){
    
    for (int i = 0; i < _tabBullets.size(); i++) {
        delete _tabBullets[i];
    }
    
    _tabBullets.clear();
    
}

//move all the bullet
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

/*
 * GETTERS
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

int Level::getEnemiesNumber() const{
    return (int)_tabEnemies.size();
}

int Level::getNbEnemies() const{
    return _nbEnemies;
}

int Level::getLevelNumber() const{
    return _levelNumber;
}
        
int Level::getNumberOfBullets() const{
    return (int)_tabBullets.size();
}

int Level::getNumberOfEnemies() const{
    return (int)_tabEnemies.size();
}

/*
 * SETTERS
 */
void Level::setNbEnemies(int nbEnemies){
    _nbEnemies = nbEnemies;
}

void Level::setLevelNumber(int levelNumber){
    _levelNumber = levelNumber;
}