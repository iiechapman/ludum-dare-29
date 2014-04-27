//
//  Background.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/27/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Background__
#define __LudumDare29__Background__

#include <iostream>
#include "GameObject.h"

class Background : public GameObject{
public:
    Background(GameObjectParams* params);
    ~Background();
    
    void draw();
    void update();
    void clean();
    
private:
    float m_speed = 3;
    
};


#endif /* defined(__LudumDare29__Background__) */
