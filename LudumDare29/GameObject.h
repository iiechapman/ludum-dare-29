//
//  GameObject.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__GameObject__
#define __LudumDare29__GameObject__

#include <iostream>
#include <string>
#include "GameObjectParams.h"
#include "TextureManager.h"

enum Direction{
    DIRECTION_DOWN,
    DIRECTION_UP,
    DIRECTION_NONE
};

using namespace std;

class GameObject{
public:
    GameObject();
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    
    virtual ~GameObject();
    
    GameObjectParams* GetParams() const;
    
protected:
    GameObjectParams* m_params;
    
};



#endif /* defined(__LudumDare29__GameObject__) */
