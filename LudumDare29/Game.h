//
//  Game.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Game__
#define __LudumDare29__Game__

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Player.h"


using namespace std;

class Game{
public:
    ~Game();
    
    static Game* Instance();
    
    SDL_Renderer* getRenderer();
    bool running();
    
    bool init(int width, int height, string name);
    void handleEvents();
    void update();
    void render();
    void quit();
    void clean();

    void initTest();
    void loadTest();
    void runTest();
    
    
private:
    Game();
    static Game* s_pInstance;
    
    string m_Name;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_running;
    
    vector<GameObject*> m_gameObjects;
};



#endif /* defined(__LudumDare29__Game__) */
