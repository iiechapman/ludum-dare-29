//
//  Player.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Player.h"
#include "Game.h"
#include "InputHandler.h"

Player::Player(GameObjectParams* params){
    m_params = params;
}

Player::~Player(){
    //cout << "Deleted player\n";
}


void Player::draw(){
    TextureManager::Instance()->draw(m_params->getTextureID(),
                                    m_params->getX(),m_params->getY(),
                                    m_params->getWidth(),m_params->getHeight(),
                                    Game::Instance()->getRenderer());
}

void Player::update(){
    
    CheckSpecialModes();
    
    m_mousePos.x =InputHandler::Instance()->getMousePos().x - 50;
    m_mousePos.y =InputHandler::Instance()->getMousePos().y - 30;

    if (m_params->getX() < m_mousePos.x ){
        m_params->setX(m_params->getX() + m_velocity.x);
    }
    
    if (m_params->getX() > m_mousePos.x ){
        m_params->setX(m_params->getX() - m_velocity.x);
    }
    
    
    if (m_params->getY() < m_mousePos.y ){
        m_params->setY(m_params->getY() + m_velocity.y);
    }
    
    if (m_params->getY() > m_mousePos.y ){
        m_params->setY(m_params->getY() - m_velocity.y);
    }
    
}

void Player::CheckSpecialModes(){
    //Check special modes
    if (turboMode){
        m_velocity.x = m_turboSpeed.x;
        m_velocity.y = m_turboSpeed.y;
    } else {
        m_velocity.x = m_baseSpeed.x;
        m_velocity.y = m_baseSpeed.y;
    }
    
    
    if (miniMode){
        //make smaller
        if (GetParams()->getWidth() > m_miniSize.x){
            GetParams()->setWidth(GetParams()->getWidth() - m_resizeSpeed);
        }
        
        if (GetParams()->getHeight() > m_miniSize.y){
            GetParams()->setHeight(GetParams()->getHeight() - m_resizeSpeed);
        }
        
    } else {
        //make normal size
        
        if (GetParams()->getWidth() < m_baseSize.x){
            GetParams()->setWidth(GetParams()->getWidth() + m_resizeSpeed);
        }
        
        if (GetParams()->getHeight() < m_baseSize.y){
            GetParams()->setHeight(GetParams()->getHeight() + m_resizeSpeed);
        }
    }
    
    
    if (shieldMode){
        //add shield dont get hurt
    } else {
        //get hurt, hide shield
    }
    
}

void Player::clean(){
    cout << "Cleaned player\n";
}








































































//END