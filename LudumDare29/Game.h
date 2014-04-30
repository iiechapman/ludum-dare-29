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
#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include "GameObject.h"
#include "Background.h"


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

    void loadData();
    void start();
    void run();
    void PlaceEntranceMarker();
    void PlaceBubble(string type, int x, int y, float x_speed, float y_speed);
    void BubbleSplash(int numBubbles);
    
    static int getLevel();
    static void setLevel(int level);
    static void resetMiles();
    
private:
    Game();
    static Game* s_pInstance;
    
    void BubbleFill(int numBubbles);
    
    void PlaceSpike();
    void PlaceTrail();
    void PlaceBubble();
    void PlaceMileMarker();
    void PlaceMarker();
    void PlacePowerup();
    
    void ClearOffscreenObjects();
    
    string m_Name;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_running;

    static int s_level;
    
    int m_markerTimer;
    int m_markerTimerTick = 50;
    
    int m_mileCoolDownTime = 10;
    int m_mileCoolDownTimer = m_mileCoolDownTime;
    
    float m_trailSpeedMod = .8;
    float m_trailSpeed = m_trailSpeedMod;
    
    int m_trailTimer;
    int m_trailTimerTick = 4;
    
    int m_spikeTimer;
    int m_spikeTimerTick = 100;
    
    int m_powerupTimer;
    int m_powerupTimerTick = 100;
    
    int m_powerupOdds = 100;
    int m_spikeOdds = 1000;
    
    static int m_bubblesPassed;
    static int m_bubblesPerMile;
    
    static int m_milesPassed;
    
    int m_hiScore = 0;
    
    vector<GameObject*> m_gameObjects;
    vector<GameObject*> m_backgroundObjects;
    vector<GameObject*> m_foregroundObjects;
    
    Background* title;
    Background* score;
    Background* hi_score;
    Background* cursor;
    
    
};



#endif /* defined(__LudumDare29__Game__) */







































































//END