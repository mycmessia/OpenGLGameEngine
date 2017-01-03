//
//  Input.hpp
//  OGLEngine
//
//  Created by 梅宇宸 on 17/1/3.
//  Copyright © 2017年 梅宇宸. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window;

class Input
{
friend class Window;
    
public:
    static GLboolean IsKeyDown (int key);
    static GLboolean IsKeyPress (int key);
    
private:
    static GLboolean keysProcessed[1024];
    static GLboolean keys[1024];
    
    
};

#endif /* Input_hpp */
