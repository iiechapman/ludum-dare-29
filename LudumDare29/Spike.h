//
//  Spike.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/27/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Spike__
#define __LudumDare29__Spike__

#include <iostream>
#include "GameObject.h"

using namespace std;

class Spike : public GameObject{
public:
    Spike(GameObjectParams* params);
    ~Spike();
    
    void draw();
    void update();
    void clean();
    
private:
    Direction m_direction;
    
};


#endif /* defined(__LudumDare29__Spike__) */
