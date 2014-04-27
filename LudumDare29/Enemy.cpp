//
//  Enemy.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <random>
#include "Enemy.h"
#include "Game.h"

int Enemy::s_numEnemies = 0;
bool Enemy::s_syncMovement = false;
Direction Enemy::s_syncDirection = DIRECTION_NONE;
float Enemy::s_upperBounds = 1000;
float Enemy::s_lowerBounds = 0;

Enemy* Enemy::s_topEnemy = 0;
Enemy* Enemy::s_bottomEnemy = 0;

Enemy::Enemy(GameObjectParams* params){
    m_params        = params;
    m_upperMax      = 50;
    m_lowerMax      = 550;
    m_padding       = 200;
    m_upperBounds   = m_upperMax;
    m_lowerBounds   = m_lowerMax;
    m_speed         = Game::Instance()->getLevel() * .5;
    m_randomization = 100;
    s_numEnemies++;
    
    s_topEnemy = s_bottomEnemy = this;
}

Enemy::~Enemy(){
    cout << "Deleted Enemy\n";
}

void Enemy::draw(){
    TextureManager::Instance()->draw(m_params->getTextureID(),
                                     m_params->getX(),m_params->getY(),
                                     m_params->getWidth(),m_params->getHeight(),
                                     Game::Instance()->getRenderer());
}

void Enemy::update(){
    m_speed = Game::Instance()->getLevel() * .2;
    
    m_randomization = (200 - Game::Instance()->getLevel()) + 20;
    
    m_padding = abs(100 - Game::Instance()->getLevel()) + 200;
    
    //m_upperBounds = m_upperMax;
    m_lowerBounds = m_lowerMax;
    
    if (s_numEnemies > 1){
        CheckAbove();
        CheckBelow();
    }
    
    Randomize();
    CheckBounds();
    
    if (m_currentDir == DIRECTION_UP){
        m_params->getVelocity().y = -m_speed;
    }
    
    if (m_currentDir == DIRECTION_DOWN){
        m_params->getVelocity().y = m_speed;
    }
    
    if (m_currentDir == DIRECTION_NONE){
        m_params->getVelocity().y = 0;
    }
    
    m_params->setY( m_params->getY() + m_params->getVelocity().y );
    
    
}

void Enemy::CheckBounds(){
    if (m_upperBounds < m_upperMax){
        cout << "Raising bounds\n";
        m_upperBounds = m_upperMax;
    }
    
    if (m_lowerBounds > m_lowerMax){
        cout << "Lowering bounds\n";
        m_lowerBounds = m_lowerMax;
    }
    
    
    if (m_params->getY() < m_upperBounds ){
        //cout << "upper b: " << m_upperBounds << endl;
        m_currentDir = DIRECTION_DOWN;
    }
    
    
    if (m_params->getY() > m_lowerBounds ){
        //cout << "lower b:" << m_lowerBounds << endl;
        m_currentDir = DIRECTION_UP;
    }
    
    
    //Check for top and bottom enemy on screen
    for(auto enemy : Game::Instance()->GetObjects("foreground")){
        if (enemy->GetParams()->isEnemy()) {
            if (enemy->GetParams()->getY() > GetBottomEnemy()->GetParams()->getY()){
                s_bottomEnemy = dynamic_cast<Enemy*>(enemy);
            }
            
            if (enemy->GetParams()->getY() < GetTopEnemy()->GetParams()->getY()){
                s_topEnemy = dynamic_cast<Enemy*>(enemy);
            }
        }
    }
    
    //update global bounds
    s_upperBounds = s_topEnemy->GetParams()->getY();
    s_lowerBounds = s_bottomEnemy->GetParams()->getY();
    
//    if (m_params->getY() > bottomEnemy->GetParams()->getY()){
//        bottomEnemy = this;
//        s_lowerBounds = m_params->getY();
//        cout << "Lowest bound: " << s_lowerBounds << endl;
//        cout << m_params->getName() << endl;
//    }
//    
//    if (m_params->getY() < topEnemy->GetParams()->getY()){
//        topEnemy = this;
//        s_upperBounds = m_params->getY();
//        cout << "highest bound: " << s_upperBounds << endl;
//        cout << m_params->getName() << endl;
//    }
//    
}

void Enemy::Randomize(){
    if (m_randomization < 4){
        m_randomization = 4;
    }
    
    int random = rand() % m_randomization;
    
    switch (random) {
        case 1:
        case 2:
            m_currentDir = DIRECTION_UP;
            //cout << "going up" << endl;
            break;
            
        case 4:
        case 5:
            m_currentDir = DIRECTION_DOWN;
            //cout << "going down" << endl;
            break;
            
        case 7:
        case 8:
        case 9:
        case 10:
            m_currentDir = DIRECTION_NONE;
            //cout << "staying still" << endl;
            break;
            
            
        case 11:
            s_syncMovement = true;
            random = rand() % 3;
            s_syncDirection = Direction(random);
            //cout << "Direction: " << s_syncDirection << endl;
            break;
            
        case 20:
            if (s_syncMovement){
                s_syncMovement = false;
                //cout << "End sync" << endl;
            }
            break;
            
        default:
            break;
    }
    
    if (s_syncMovement == true){
        m_currentDir = s_syncDirection;
        //cout << "Sync " << m_params->getName() << endl;
    }
    
}

void Enemy::CheckAbove(){
    if (s_numEnemies > 1){
        for (auto enemy : Game::Instance()->GetObjects("foreground")){
            if (this != enemy && enemy->GetParams()->isEnemy()){
                int enemy_Y = enemy->GetParams()->getY();
                if (enemy_Y < m_params->getY()){
                    if (enemy_Y > m_upperBounds){
                        m_upperBounds = enemy_Y + m_padding;
                        //cout << "change upper " << m_upperBounds << endl;
                    }
                }
            }
        }
    }
}

void Enemy::CheckBelow(){
    if (s_numEnemies > 1){
        for (auto enemy : Game::Instance()->GetObjects("foreground")){
            if (this != enemy && enemy->GetParams()->isEnemy()){
                int enemy_Y = enemy->GetParams()->getY();
                if (enemy_Y > m_params->getY()){
                    if (enemy_Y < m_lowerBounds){
                        m_lowerBounds = enemy_Y - m_padding;
                        ////cout << "change lower " << m_lowerBounds << endl;
                    }
                }
            }
        }
    }
}

void Enemy::clean(){
    cout << "Cleaned Enemy\n";
}








































































//END