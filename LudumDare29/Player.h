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
    
};

#endif /* defined(__LudumDare29__Player__) */
