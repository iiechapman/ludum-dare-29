//
//  Powerup.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/27/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Powerup__
#define __LudumDare29__Powerup__

#include <iostream>
#include "GameObject.h"

using namespace std;

class Powerup : public GameObject{
public:
    Powerup(GameObjectParams* params);
    ~Powerup();
    
    void draw();
    void update();
    void clean();
    
private:
    Direction m_direction = DIRECTION_NONE;
    int m_alpha;
};


#endif /* defined(__LudumDare29__Powerup__) */
