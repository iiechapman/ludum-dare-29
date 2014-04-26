//
//  GameObjectParams.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__GameObjectParams__
#define __LudumDare29__GameObjectParams__

#include <iostream>
#include <string>

struct Vector2D{
    Vector2D(int _x, int _y)
    :x(_x),y(_y){}
    
    int x,y;
};

using namespace std;

class GameObjectParams{
public:
    GameObjectParams();
    GameObjectParams(string name,int x, int y, int width, int height,Vector2D velocity, string textureID);
    ~GameObjectParams();
    
    GameObjectParams* operator=(GameObjectParams rhs);
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_width; }
    
    Vector2D& getVelocity(){ return m_velocity; }
    
    string getName() const { return m_name; }
    string getTextureID() const { return m_textureID; }
    
    void setX(int x){ m_x = x;}
    void setY(int y){ m_y = y;}
    
    
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    Vector2D m_velocity;
    string m_name;
    string m_textureID;
};

#endif /* defined(__LudumDare29__GameObjectParams__) */
