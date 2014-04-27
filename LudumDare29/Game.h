//
//  Game.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__Game__
#define __LudumDare29__Game__

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "GameObject.h"

using namespace std;

class Game{
public:
    ~Game();
    
    static Game* Instance();
    
    SDL_Renderer* getRenderer();
    vector<GameObject*> GetObjects(string layer);
    
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
    
    static int getLevel();
    
private:
    Game();
    static Game* s_pInstance;
    
    void PlaceSpike();
    void PlaceTrail();
    void PlaceBubble();
    void PlaceMileMarker();
    
    string m_Name;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_running;

    static int s_level;
    
    int m_mileTimer;
    int m_mileTimerTick = 30;
    
    float m_trailSpeed = -3;
    
    int m_trailTimer;
    int m_trailTimerTick = 4;
    
    int m_spikeTimer;
    int m_spikeTimerTick = 100;
    
    vector<GameObject*> m_gameObjects;
    vector<GameObject*> m_backgroundObjects;
    vector<GameObject*> m_foregroundObjects;
    
};



#endif /* defined(__LudumDare29__Game__) */







































































//END