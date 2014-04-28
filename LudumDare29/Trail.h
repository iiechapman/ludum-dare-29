//
//  Trail.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Trail__
#define __LudumDare29__Trail__

#include <iostream>
#include "GameObject.h"

using namespace std;

class Trail : public GameObject{
public:
    Trail(GameObjectParams* params);
    ~Trail();
    
    void draw();
    void update();
    void clean();
    
private:
};


#endif /* defined(__LudumDare29__Trail__) */
