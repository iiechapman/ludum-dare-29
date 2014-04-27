//
//  Background.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/27/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Background.h"

#include "Game.h"

Background::Background(GameObjectParams* params){
    m_params = params;
}

Background::~Background(){
    //cout << "Deleted Background\n";
}


void Background::draw(){
    TextureManager::Instance()->draw(m_params->getTextureID(),
                                     m_params->getX(),m_params->getY(),
                                     m_params->getWidth(),m_params->getHeight(),
                                     Game::Instance()->getRenderer());
}

void Background::update(){
    

}

void Background::clean(){
    cout << "Cleaned Background\n";
}