//
//  TextureManager.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager* TextureManager::Instance(){
    if (!s_pInstance){
        s_pInstance = new TextureManager();
    }
    return s_pInstance;
}

TextureManager::TextureManager(){
    cout << "Initializing Texture Manager\n";
    IMG_Init(IMG_INIT_PNG);
}

TextureManager::~TextureManager(){
    cout << "Deleting texture manager\n";
}

bool TextureManager::load(string fileName, string textureID, SDL_Renderer* pRenderer){
    
    SDL_Surface* p_tempSurface = IMG_Load(fileName.c_str());
    
    SDL_Texture* p_tempTexture =
    SDL_CreateTextureFromSurface(pRenderer, p_tempSurface);
    
    SDL_FreeSurface(p_tempSurface);
    
    if (p_tempTexture){
        m_textureMap[textureID] = p_tempTexture;
        cout << "Texture load succesful\n";
        return true;
    }
    
    cout << "Texture load unsuccessful\n";
    return false;
}

void TextureManager::draw(string textureID,
                          float x, float y, float width, float height, SDL_Renderer* pRenderer){
    
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(m_textureMap[textureID], 0, 0, &srcRect.w, &srcRect.h);
    
    dstRect.w = width;
    dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;
    
    SDL_RenderCopyEx(pRenderer, m_textureMap[textureID],
                     &srcRect, &dstRect, 0.0,0, SDL_FLIP_NONE);
}

void TextureManager::clearTextureMap(){
    m_textureMap.clear();
}

void TextureManager::clean(){
    cout << "Cleaning texture manager\n";
}


