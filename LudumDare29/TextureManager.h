//
//  TextureManager.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__TextureManager__
#define __LudumDare29__TextureManager__

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

class TextureManager{
public:
    ~TextureManager();
    
    static TextureManager* Instance();
    
    bool load(string fileName, string textureID, SDL_Renderer* pRenderer);
    void draw(string textureID, int x, int y,
              int width, int height, SDL_Renderer* pRenderer);
    
    void clearTextureMap();
    void clean();
    
    
private:
    TextureManager();
    static TextureManager* s_pInstance;
    
    map<string, SDL_Texture*> m_textureMap;
    
};

#endif /* defined(__LudumDare29__TextureManager__) */
