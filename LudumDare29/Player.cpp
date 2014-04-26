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
    cout << "Deleted player\n";
}


void Player::draw(){
    TextureManager::Instance()->draw(m_params->getTextureID(),
                                    m_params->getX(),m_params->getY(),
                                    m_params->getWidth(),m_params->getHeight(),
                                    Game::Instance()->getRenderer());
}

void Player::update(){
    
    bool verticalPressed =
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ||
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN);
    
    bool horizontalPressed =
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)||
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT);
    
    if (!horizontalPressed){
          m_params->getVelocity().x = 0;
    }
    
    if (!verticalPressed){
         m_params->getVelocity().y = 0;
    }
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
        m_params->getVelocity().y = -2;
    }
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)){
        m_params->getVelocity().y = 2;
    }
    

    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
        m_params->getVelocity().x = 2;
    }
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)){
        m_params->getVelocity().x = -2;
    }
    
    m_params->setX( m_params->getX() + m_params->getVelocity().x );
    m_params->setY( m_params->getY() + m_params->getVelocity().y );
}

void Player::clean(){
    cout << "Cleaned player\n";
}