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
    Vector2D(float _x, float _y)
    :x(_x),y(_y){}
    
    float x,y;
};

using namespace std;

class GameObjectParams{
public:
    GameObjectParams();
    GameObjectParams(string name,float x, float y, float width, float height,
                     Vector2D velocity,bool isHazard,bool isEnemy , string textureID);
    ~GameObjectParams();
    
    GameObjectParams* operator=(GameObjectParams rhs);
    
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getWidth() const { return m_width; }
    float getHeight() const { return m_height; }
    bool isHazard() const { return m_isHazard; }
    bool isEnemy() const { return m_isEnemy; }
    
    Vector2D& getVelocity(){ return m_velocity; }
    
    string getName() const { return m_name; }
    string getTextureID() const { return m_textureID; }
    
    void setX(float x){ m_x = x;}
    void setY(float y){ m_y = y;}
    void setWidth(float width){ m_width = width;}
    void setHeight(float height){ m_height = height;}
    void setHazard(bool hazard){ m_isHazard = hazard; }
    
    
protected:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    Vector2D m_velocity;
    string m_name;
    string m_textureID;
    bool m_isHazard;
    bool m_isEnemy;
    
};

#endif /* defined(__LudumDare29__GameObjectParams__) */








































































//END