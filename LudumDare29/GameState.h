//
//  GameState.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__GameState__
#define __LudumDare29__GameState__

#include <iostream>
#include <vector>
#include "GameObject.h"

using namespace std;


class GameState{
public:
    GameState();
    ~GameState();
    
    
    
protected:
    vector<GameObject*> m_gameObjects;
    
    
    
};


#endif /* defined(__LudumDare29__GameState__) */
