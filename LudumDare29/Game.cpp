//
//  Game.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <cmath>
#include "Game.h"
#include "InputHandler.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Trail.h"
#include "Spike.h"


Game* Game::s_pInstance = 0;

int Game::s_level = 1;

Game* Game::Instance(){
    if (!s_pInstance){
        s_pInstance = new Game();
    }
    return s_pInstance;
}

Game::Game()
:m_running(true){
    cout << "Created new Game\n";
}

Game::~Game(){
    cout << "Deleting Game\n";
}

bool Game::running(){
    return m_running;
}

SDL_Renderer* Game::getRenderer(){
    return m_pRenderer;
}

vector<GameObject*> Game::GetObjects(string layer){
    if (layer == "gameobject"){
        return m_gameObjects;
    }
    
    if (layer == "foreground"){
        return m_foregroundObjects;
    }
    
    if (layer == "background"){
        return m_backgroundObjects;
    }
    
    
    return m_gameObjects;
}

bool Game::init(int width, int height, string name){
    cout << "Init game\n";
    
    m_Name = name;
    
    // Initialize the SDL library.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return false;
	}
	
	m_pWindow = SDL_CreateWindow(m_Name.c_str(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,
                                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
    if (m_pWindow && m_pRenderer){
        cout << "Created window and renderer successfully\n";
        return true;
    }
    
    return false;
}

void Game::handleEvents(){
    InputHandler::Instance()->update();
}

void Game::update(){
    for (auto gameObject : m_gameObjects){
        gameObject->update();
    }
    
    for (auto gameObject : m_foregroundObjects){
        gameObject->update();
    }
    
    for (auto gameObject : m_backgroundObjects){
        gameObject->update();
    }
    
    //clear old items off screen
    if (m_backgroundObjects.size() > 0){
        auto gameObject = m_backgroundObjects.begin();
        
        while (gameObject !=m_backgroundObjects.end()){
            if ((*gameObject)->GetParams()->getX() < -100
                && ((*gameObject)->GetParams()->isHazard() ||
                    (*gameObject)->GetParams()->isEnemy())){
                    //cout << "object deleted\n";
                    delete (*gameObject);
                    (*gameObject) = nullptr;
                    gameObject = m_backgroundObjects.erase(gameObject);
                } else {
                    gameObject++;
                }
        }
    }
    
    if (m_gameObjects.size() > 0){
        auto gameObject = m_gameObjects.begin();
        
        while (gameObject !=m_gameObjects.end()){
            if ((*gameObject)->GetParams()->getX() < -100
                && ((*gameObject)->GetParams()->isHazard() ||
                    (*gameObject)->GetParams()->isEnemy())){
                    //cout << "object deleted\n";
                    delete (*gameObject);
                    (*gameObject) = nullptr;
                    gameObject = m_gameObjects.erase(gameObject);
                } else {
                    gameObject++;
                }
        }
    }
    
    //cout << "Total objects on screen " << m_gameObjects.size() << endl;
    
    
}

void Game::render(){
    SDL_SetRenderDrawColor(m_pRenderer, 0, 191, 255, 255);
    SDL_RenderClear(m_pRenderer);
    
    for (auto gameObject : m_backgroundObjects){
        gameObject->draw();
    }
    
    for (auto gameObject : m_gameObjects){
        gameObject->draw();
    }
    
    for (auto gameObject : m_foregroundObjects){
        gameObject->draw();
    }
    
    
    
    SDL_RenderPresent(m_pRenderer);
}

void Game::quit(){
    cout << "Quit action processed\n";
    m_running = false;
}

void Game::clean(){
    cout << "Cleaning game\n";
    
    if (m_pWindow){
        SDL_DestroyWindow(m_pWindow);
        SDL_DestroyRenderer(m_pRenderer);
        SDL_Quit();
    }
}

void Game::initTest(){
    TextureManager::Instance()->load("shipnew.png", "playership", m_pRenderer);
    TextureManager::Instance()->load("ship2.png", "enemyship", m_pRenderer);
    TextureManager::Instance()->load("bubble.png", "bubble", m_pRenderer);
    TextureManager::Instance()->load("spike.png", "spike", m_pRenderer);
    TextureManager::Instance()->load("badtrail.png", "bluetrail", m_pRenderer);
    TextureManager::Instance()->load("redtrail.png", "redtrail", m_pRenderer);
    TextureManager::Instance()->load("bg2.png", "bg1", m_pRenderer);
    
    TextureManager::Instance()->load("capsule_mini.png", "capsule_mini", m_pRenderer);
    TextureManager::Instance()->load("capsule_turbo.png", "capsule_turbo", m_pRenderer);
    TextureManager::Instance()->load("capsule_shield.png", "capsule_shield", m_pRenderer);
    
}

void Game::loadTest(){
    
    m_backgroundObjects.push_back
    (new Background(new GameObjectParams("background",0,0,1136,640,{0,0},false,false,"bg1")));
    
    
    m_foregroundObjects.push_back
    (new Player(new GameObjectParams("player",100,200,86,55,{0,0},false,false,"playership")));
    
    
    m_foregroundObjects.push_back
    (new Enemy(new GameObjectParams("enemy1",1100,200,75,46,{0,-1},false,true,"enemyship")));
    
    m_foregroundObjects.push_back
    (new Enemy(new GameObjectParams("enemy2",1100,400,75,46,{0,-1},false,true,"enemyship")));
    
    for (auto enemy : m_foregroundObjects){
        if (enemy->GetParams()->isEnemy()){
            m_gameObjects.push_back
            (new Trail(new GameObjectParams("trail",
                                            enemy->GetParams()->getX() - 60,
                                            enemy->GetParams()->getY() - 30,
                                            100,100,{m_trailSpeed,0},true,false,"redtrail")));
        }
    }
    
    
}

void Game::runTest(){
    
    //Tick timers
    m_trailTimer++;
    m_mileTimer++;
    m_spikeTimer++;
    
    //Speed up trail timer based on level
    m_trailTimerTick = 18 - s_level;
    if (m_trailTimerTick <= 1 ){
        m_trailTimerTick = 1;
    }
    
    if (m_trailTimer >= m_trailTimerTick ){
        PlaceSpike();
        PlaceTrail();
        PlaceBubble();
        m_trailTimer = 0;
    }
    
    if (m_mileTimer >= m_mileTimerTick){
        m_trailSpeed = -s_level * .6;
        s_level++;
        PlaceMileMarker();
        m_mileTimer = 0;
    }
    
    
    //Cap level so game isnt too fast
    if (s_level >= 50){
        s_level  = 50;
    }
    
    m_trailTimerTick = 50 / abs(m_trailSpeed);
    
    //Update all scrolling objects to match speed
    for (auto enemy : m_gameObjects){
        if (enemy->GetParams()->isHazard()){
            enemy->GetParams()->getVelocity().x = m_trailSpeed;
        }
    }
}


int Game::getLevel(){
    return s_level;
}


void Game::PlaceBubble(){
    //Add bubbles in background
    float randomSize =-(rand()%5) + 15 +(rand()%25) ;
    m_backgroundObjects.push_back
    (new Trail(new GameObjectParams("bubble",
                                    1100,
                                    rand() % 700,
                                    randomSize,randomSize,
                                    {static_cast<float>(m_trailSpeed * (randomSize * .02)),0},false,false,"bubble")));
    
}

void Game::PlaceSpike(){
    int placeSpike = rand() % 2000 - s_level;
    
    if (placeSpike <= 2){

        int endRange = Enemy::GetLowerBounds() - Enemy::GetUpperBounds() + 1 ;
        int beginRange = Enemy::GetUpperBounds() + 1;
        
        int position =
        rand() % endRange + beginRange;
        
        float randomSize =-(rand()%2) + 45 +(rand()%45) ;
        m_foregroundObjects.push_back
        (new Spike(new GameObjectParams("spike",
                                        1100,
                                        position ,
                                        randomSize,randomSize,
                                        {static_cast<float>(m_trailSpeed * (randomSize * .01)),0},false,false,"spike")));
        
    }
    
}

void Game::PlaceTrail(){
    //Create trail every trail tick
        for (auto enemy : m_foregroundObjects){
            if (enemy != 0){
                if (enemy->GetParams()->isEnemy()){
                    m_gameObjects.push_back
                    (new Trail(new GameObjectParams("trail",
                                                    enemy->GetParams()->getX() - 20,
                                                    enemy->GetParams()->getY(),
                                                    40,40,{m_trailSpeed,0},true,false,"bluetrail")));
                }
            }
        }
    }

void Game::PlaceMileMarker(){
    //Place "mile marker" buoys
        for (auto enemy : m_foregroundObjects){
            if (enemy->GetParams()->isEnemy()){
                m_gameObjects.push_back
                (new Trail(new GameObjectParams("redtrail",
                                                enemy->GetParams()->getX() - 20,
                                                enemy->GetParams()->getY() -10,
                                                50,50,{m_trailSpeed,0},true,false,"redtrail")));
            }
        }
        
    }


























































//END