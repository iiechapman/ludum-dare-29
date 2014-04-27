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
    
    Vector2D m_baseSpeed{10,5};
    Vector2D m_turboSpeed{30,20};
    Vector2D m_velocity{m_baseSpeed.x,m_baseSpeed.y};
    Vector2D m_mousePos{0,0};
    
    Vector2D m_baseSize{86,55};
    Vector2D m_miniSize{43,27};
    
    bool turboMode = false;
    bool miniMode = false;
    bool shieldMode = false;
    
    float m_resizeSpeed = .8;
    
};

#endif /* defined(__LudumDare29__Player__) */
