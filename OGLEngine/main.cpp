//
//  main.cpp
//  GameEngine
//
//  Created by 梅宇宸 on 17/1/2.
//  Copyright © 2017年 梅宇宸. All rights reserved.
//

#include <iostream>

#include "Engines/Input.hpp"
#include "Engines/Window.hpp"
#include "Engines/Shader.hpp"
#include "Engines/Loader.hpp"
#include "Engines/Renderer.hpp"

int main (int argc, const char * argv[])
{
    Window window (800, 600);
    Renderer renderer;
    
    float vertices[] = {
        -0.2f,  0.2f, 0.0f,
        -0.2f, -0.2f, 0.0f,
         0.2f, -0.2f, 0.0f,
         0.2f,  0.2f, 0.0f
    };
    
    int indices[] = {
        0, 1, 3,
        3, 1, 2
    };

    RawModel model = Loader::LoadToVAO (
        vertices, sizeof (vertices) / sizeof (float),
        indices, sizeof (indices) / sizeof (int)
    );
    
    Loader::LoadShader (SHADER_FULL_DIR"basic.vs", SHADER_FULL_DIR"basic.frag", nullptr, "basic");
    
    while (!window.IsClose ())
    {
        window.Clear (GL_COLOR_BUFFER_BIT);
        
        window.PullEvents ();
        
        if (Input::IsKeyDown(GLFW_KEY_SPACE))
        {
            std::cout << "Space down" << std::endl;;
        }
        
        if (Input::IsKeyPress(GLFW_KEY_1))
        {
            std::cout << "1 down" << std::endl;
        }
        
        
        Loader::GetShader ("basic").Use ();
        
        renderer.render (model);
        
        window.SwapBuffer ();
    }
    
    return 0;
}
