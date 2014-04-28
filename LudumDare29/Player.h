//
//  Player.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Player__
#define __LudumDare29__Player__

#include <iostream>
#include "GameObject.h"

class Player : public GameObject{
public:
    Player(GameObjectParams* params);
    ~Player();
    
    void draw();
    void update();
    void clean();
    
private:
    void CheckSpecialModes();
    void CheckCollisions();
    void EjectBubble();
    
    Vector2D m_baseSpeed{8,4};
    Vector2D m_turboSpeed{16,10};
    Vector2D m_velocity{m_baseSpeed.x,m_baseSpeed.y};
    Vector2D m_mousePos{0,0};
    
    Vector2D m_baseSize{86,55};
    Vector2D m_miniSize{43,27};
    
    bool m_turboMode = false;
    bool m_miniMode = false;
    bool m_shieldMode = false;
    
    int m_turboTimer = 0;
    int m_turboTime = 400;
    
    int m_miniTimer = 0;
    int m_miniTime = 400;
    
    int m_shieldTimer= 0;
    int m_shieldTime = 300;
    
    int m_exhaustTimer  = 0;
    int m_normalExhaust = 10;
    int m_turboExhaust  = 5;

    float m_normalExhaustSpeed = .06;
    float m_turboExhaustSpeed = .09;
    float m_exhastSpeed = m_normalExhaustSpeed;
    
    int m_exhaustTime = m_normalExhaust;
    
    float m_resizeSpeed = .9;
    
    int m_alpha;
    
};

#endif /* defined(__LudumDare29__Player__) */
