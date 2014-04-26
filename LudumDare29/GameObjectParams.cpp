//
//  GameObjectParams.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "GameObjectParams.h"

GameObjectParams::GameObjectParams():
GameObjectParams("null object",0,0,20,20,Vector2D{0,0}, "null")
{
    cout << "Null params\n";
}


GameObjectParams::GameObjectParams(string name,int x, int y,
                                   int width, int height,
                                   Vector2D velocity, string textureID):
m_x(x),
m_y(y),
m_width(width),
m_height(height),
m_velocity(velocity.x, velocity.y),
m_name(name),
m_textureID(textureID)
{
    cout << "at constructor\n";
    cout << m_velocity.x << endl;
    cout << m_velocity.y << endl;
    
    cout << "Sent in values\n";
    cout << velocity.x << endl;
    cout << velocity.y << endl;
}

GameObjectParams::~GameObjectParams(){
    cout << "Deleted game object parameters\n";
}


GameObjectParams* GameObjectParams::operator=(GameObjectParams rhs){
    m_x             = rhs.m_x;
    m_y             = rhs.m_y;
    m_width         = rhs.m_width;
    m_height        = rhs.m_height;
    
    m_name          = rhs.m_name;
    m_textureID     = rhs.m_textureID;
    
    return this;
}