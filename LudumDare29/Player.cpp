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
#include "SoundManager.h"
#include "Trail.h"

Player::Player(GameObjectParams* params){
    m_params = params;
}

Player::~Player(){
    delete m_params;
    m_params = 0;
    //cout << "Deleted player\n";
}


void Player::draw(){
    TextureManager::Instance()->draw(m_params->getTextureID(),
                                     m_params->getX(),m_params->getY(),
                                     m_params->getWidth(),m_params->getHeight(),m_alpha,
                                     Game::Instance()->getRenderer());
}

void Player::update(){
    
    CheckSpecialModes();
    
    m_exhaustTimer--;
    
    if (m_exhaustTimer <=0 ){
        EjectBubble();
        m_exhaustTimer = m_exhaustTime;
    }
    
    m_mousePos.x =InputHandler::Instance()->getMousePos().x - 150;
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
    
    CheckCollisions();
    
}

void Player::EjectBubble(){
    //SoundManager::Instance()->playSound("smallbubble");
        Game::Instance()->PlaceBubble("smokebubble",GetParams().getX() - 10, GetParams().getY() + 10 , m_exhastSpeed,0);
    }


void Player::CheckSpecialModes(){
    //Check special modes
    
    //lose powerup sounds
    if (m_turboTimer <= 0 && m_turboMode){
        SoundManager::Instance()->playSound("losepowerup");
    }
    
    if (m_miniTimer <= 0 && m_miniMode){
        SoundManager::Instance()->playSound("losepowerup");
    }
    
    if (m_shieldTimer <= 0 && m_shieldMode){
        SoundManager::Instance()->playSound("losepowerup");
        m_alpha = 0;
    }
    
    m_turboMode  = m_turboTimer > 0;
    m_miniMode   = m_miniTimer > 0;
    m_shieldMode = m_shieldTimer > 0;

    
    if (m_turboMode){
        m_velocity.x = m_turboSpeed.x;
        m_velocity.y = m_turboSpeed.y;
        
        m_turboTimer-=1;
        
        m_exhaustTime = m_turboExhaust;
        m_exhastSpeed = m_turboExhaustSpeed;
        
    } else {
        m_velocity.x = m_baseSpeed.x;
        m_velocity.y = m_baseSpeed.y;
        
        m_exhaustTime = m_normalExhaust;
        m_exhastSpeed = m_normalExhaustSpeed;
    }
    
    
    if (m_miniMode){
        //make smaller
        if (GetParams().getWidth() > m_miniSize.x){
            GetParams().setWidth(GetParams().getWidth() - m_resizeSpeed);
        }
        
        if (GetParams().getHeight() > m_miniSize.y){
            GetParams().setHeight(GetParams().getHeight() - m_resizeSpeed);
        }
        m_miniTimer -= 1;
        
    } else {
        //make normal size
        
        if (GetParams().getWidth() < m_baseSize.x){
            GetParams().setWidth(GetParams().getWidth() + m_resizeSpeed);
        }
        
        if (GetParams().getHeight() < m_baseSize.y){
            GetParams().setHeight(GetParams().getHeight() + m_resizeSpeed);
        }
    }
    
    
    if (m_shieldMode){
        //add shield dont get hurt
        m_alpha +=40;
        if (m_alpha > 255){
            m_alpha = 0;
        }
        m_shieldTimer -= 1;
    } else {
        //get hurt, hide shield
        if (m_alpha < 255){
         m_alpha +=10;
            if (m_alpha >=255){
                m_alpha =255;
            }
        }
    }
    
}

void Player::CheckCollisions(){
    
    if (!m_shieldMode){
        for (auto hazard : Game::Instance()->GetObjects("foreground")){
            if (hazard != this &&  (hazard->GetParams().isHazard() || hazard->GetParams().isEnemy() )
                ){
                
                Vector2D hazPos{hazard->GetParams().getX() +5,hazard->GetParams().getY() + 5};
                Vector2D hazSize{hazard->GetParams().getWidth() -5 ,hazard->GetParams().getHeight() - 5};
                
        

                Vector2D myPos{GetParams().getX() + 25,GetParams().getY() + 25};
                Vector2D mySize{GetParams().getWidth() - 25,GetParams().getHeight() - 25};
                
                if (myPos.x + mySize.x >= hazPos.x &&
                    myPos.x <= hazPos.x + hazSize.x &&
                    myPos.y <= hazPos.y + hazSize.y &&
                    myPos.y + mySize.y >= hazPos.y){
                    
                    Game::Instance()->setLevel(Game::Instance()->getLevel() - 30);
                    
                    cout << "Death! \n" ;
                    Game::Instance()->BubbleSplash(200);
                    SoundManager::Instance()->playSound("death");
                    m_turboTimer = m_miniTimer = m_shieldTimer = 0;
                    GetParams().setY(320);
                    GetParams().setX(-100);
                    m_shieldTimer = m_shieldTime / 2;
                    Game::Instance()->resetMiles();
                }
            }
        }
    }
    
    for (auto powerup : Game::Instance()->GetObjects("foreground")){
        if (powerup != this &&  (!powerup->GetParams().isHazard() && !powerup->GetParams().isEnemy() )
            ){
            
            Vector2D hazPos{powerup->GetParams().getX(),powerup->GetParams().getY()};
            Vector2D hazSize{powerup->GetParams().getWidth(),powerup->GetParams().getHeight()};
            
            Vector2D myPos{GetParams().getX(),GetParams().getY()};
            Vector2D mySize{GetParams().getWidth(),GetParams().getHeight()};
            
            if (myPos.x + mySize.x >= hazPos.x &&
                myPos.x <= hazPos.x + hazSize.x &&
                myPos.y <= hazPos.y + hazSize.y &&
                myPos.y + mySize.y >= hazPos.y){
                
                cout << "Powerup: " ;
                
                powerup->GetParams().setX(-200);
                
                if (powerup->GetParams().getName() == "capsule_mini"){
                    cout << "MINI! \n";
                    SoundManager::Instance()->playSound("capsule_mini");
                    m_miniTimer = m_miniTime;
                }
                
                if (powerup->GetParams().getName() == "capsule_shield"){
                    cout << "SHIELD! \n";
                    SoundManager::Instance()->playSound("capsule_shield");
                    m_shieldTimer = m_shieldTime;
                }
                if (powerup->GetParams().getName() == "capsule_turbo"){
                    cout << "TURBO! \n";
                    SoundManager::Instance()->playSound("capsule_turbo");
                    m_turboTimer = m_turboTime;
                }
            }
        }
    }
    
}



void Player::clean(){
    cout << "Cleaned player\n";
}








































































//END