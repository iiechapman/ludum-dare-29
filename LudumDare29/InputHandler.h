//
//  InputHandler.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__InputHandler__
#define __LudumDare29__InputHandler__

#include <iostream>

using namespace std;

class InputHandler{
public:
    ~InputHandler();
    
    static InputHandler* Instance();
    
    void update();
    bool isKeyDown(SDL_Scancode key) const;


private:
    InputHandler();
    
    void updateKeys();
    
    static InputHandler* s_pInstance;
    const Uint8* m_keystates;
};



#endif /* defined(__LudumDare29__InputHandler__) */
