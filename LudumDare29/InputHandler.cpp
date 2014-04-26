//
//  InputHandler.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <SDL2/SDL.h>
#include "Game.h"
#include "InputHandler.h"


InputHandler* InputHandler::s_pInstance = 0;

InputHandler* InputHandler::Instance(){
    if (!s_pInstance){
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
}

InputHandler::InputHandler(){
    cout << "Created input handler\n";
}

InputHandler::~InputHandler(){
    cout << "Deleted InputHandler\n";
}

void InputHandler::update(){
    SDL_Event p_event;
    SDL_PollEvent(&p_event);
    
    switch (p_event.type)
	{
		case SDL_QUIT:
            Game::Instance()->quit();
			break;
			
		case SDL_KEYDOWN:
		{
			if (p_event.key.keysym.sym == SDLK_ESCAPE)
			{
                Game::Instance()->quit();
			}
            
            updateKeys();
            break;
		}
        
        case SDL_KEYUP:
        {
            updateKeys();
            break;
        }

	}
}

void InputHandler::updateKeys(){
    m_keystates = SDL_GetKeyboardState(0);
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    if (m_keystates){
        return m_keystates[key];
    }
    
    return false;
}
