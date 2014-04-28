//
//  Trail.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Trail.h"
#include "Game.h"


Trail::Trail(GameObjectParams* params){
    m_params = params;
}

Trail::~Trail(){
    //cout << "Deleted Trail\n";
}


void Trail::draw(){
    TextureManager::Instance()->draw(m_params->getTextureID(),
                                     m_params->getX(),m_params->getY(),
                                     m_params->getWidth(),m_params->getHeight(),255 ,
                                     Game::Instance()->getRenderer());
}

void Trail::update(){
    m_params->setX( m_params->getX() + m_params->getVelocity().x );
    m_params->setY( m_params->getY() + m_params->getVelocity().y );
}

void Trail::clean(){
    cout << "Cleaned Trail\n";
}