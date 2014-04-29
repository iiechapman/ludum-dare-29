//
//  GameObject.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "GameObject.h"


GameObject::GameObject(){
    //cout << "Made game object\n";
    m_params = 0;
}

GameObject::~GameObject(){
    delete m_params;
    m_params = 0;
    //cout << "Deleted game object\n";
}

GameObjectParams& GameObject::GetParams(){
    return *m_params;
}

