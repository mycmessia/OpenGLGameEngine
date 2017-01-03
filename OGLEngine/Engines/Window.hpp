//
//  Window.hpp
//  GameEngine
//
//  Created by 梅宇宸 on 17/1/2.
//  Copyright © 2017年 梅宇宸. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Window
{
public:
    Window (int sw, int sh);
    ~Window ();
    
    inline GLFWwindow* GetGLWindow () { return glWindow; };
    
    bool IsClose ();
    
    void PullEvents ();
    
    void Clear (GLbitfield mask);
    
    void SwapBuffer ();
    
    static void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mode);
    
private:
    GLFWwindow* glWindow;
    
    int screenWidth;
    int screenHeight;
    int framebufferWidth;
    int framebufferHeight;
};

#endif /* Window_hpp */
