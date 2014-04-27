//
//  Enemy.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Enemy__
#define __LudumDare29__Enemy__

#include <iostream>
#include "GameObject.h"

class Enemy : public GameObject{
public:
    Enemy(GameObjectParams* params);
    ~Enemy();
    
    static float GetLowerBounds() { return s_lowerBounds;}
    static float GetUpperBounds() { return s_upperBounds;}
    
    static Enemy* GetTopEnemy(){ return s_topEnemy; }
    static Enemy* GetBottomEnemy(){ return s_bottomEnemy; }
    
    void draw();
    void update();
    void clean();
    
private:
    void Randomize();
    void CheckAbove();
    void CheckBelow();
    void CheckBounds();
    void CheckCenter();
    
    Direction m_currentDir;
    
    float m_upperMax;
    float m_lowerMax;
    float m_upperBounds;
    float m_lowerBounds;
    float m_padding;
    float m_speed;
    int m_randomization;
    
    static bool s_syncMovement;
    static Direction s_syncDirection;
    static float s_upperBounds;
    static float s_lowerBounds;
    
    static Enemy* s_topEnemy;
    static Enemy* s_bottomEnemy;
    
    static int s_numEnemies;
    
};


#endif /* defined(__LudumDare29__Enemy__) */
