//
//  Game.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Game.h"
#include "InputHandler.h"

Game* Game::s_pInstance = 0;

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
                                  SDL_RENDERER_ACCELERATED);
	
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
}

void Game::render(){
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);
    
    for (auto gameObject : m_gameObjects){
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
    TextureManager::Instance()->load("sprites.png", "sprites", m_pRenderer);
    TextureManager::Instance()->load("ship1.png", "ship1", m_pRenderer);
}

void Game::loadTest(){
    
    m_gameObjects.push_back
    (new Player(new GameObjectParams("ship1",10,10,50,50,{1,1},"ship1")));
    
    m_gameObjects.push_back
    (new Player(new GameObjectParams("ship2",10,100,50,50,{2,2},"ship1")));
    
    m_gameObjects.push_back
    (new Player(new GameObjectParams("ship3",100,200,100,100,{-1,-1},"ship1")));
}

void Game::runTest(){
    
}




































































//END