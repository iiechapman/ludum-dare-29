//
//  Spike.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/27/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <random>
#include "Spike.h"
#include "Game.h"
#include "Enemy.h"


Spike::Spike(GameObjectParams* params){
    m_params = params;
    
    int random = rand() % 3;
    
    m_direction = Direction(random);
    
}

Spike::~Spike(){
    delete m_params;
    m_params = 0;
    //cout << "Deleted Spike\n";
}


void Spike::draw(){
    TextureManager::Instance()->draw(m_params->getTextureID(),
                                     m_params->getX(),m_params->getY(),
                                     m_params->getWidth(),m_params->getHeight(),255,
                                     Game::Instance()->getRenderer());
}

void Spike::update(){
    
    if (m_params->getY() < Enemy::GetTopEnemy()->GetParams().getY()){
        m_direction = DIRECTION_DOWN;
    }
    
    if (m_params->getY() > Enemy::GetBottomEnemy()->GetParams().getY()){
        m_direction = DIRECTION_UP;
    }
    
    
    switch (m_direction) {
        case DIRECTION_UP:
            m_params->getVelocity().y = -1;
            break;
            
        case DIRECTION_DOWN:
            m_params->getVelocity().y = 1;
            break;
            
        case DIRECTION_NONE:
            m_params->getVelocity().y = 0;
            break;
        
        default:
            m_params->getVelocity().y = 0;
            break;
    }

    m_params->setY( m_params->getY() + m_params->getVelocity().y );
    m_params->setX( m_params->getX() + m_params->getVelocity().x );
    
}

void Spike::clean(){
    cout << "Cleaned Spike\n";
}





















