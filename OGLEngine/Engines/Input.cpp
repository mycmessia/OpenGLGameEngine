//
//  Input.cpp
//  OGLEngine
//
//  Created by 梅宇宸 on 17/1/3.
//  Copyright © 2017年 梅宇宸. All rights reserved.
//

#include "Input.hpp"

GLboolean Input::keysProcessed[1024] = {false};
GLboolean Input::keys[1024] = {false};

GLboolean Input::IsKeyDown (int key)
{
    return keys[key];
}

GLboolean Input::IsKeyPress (int key)
{
    if (keys[key] && !keysProcessed[key])
    {
        keysProcessed[key] = true;
        return true;
    }
    
    return false;
}