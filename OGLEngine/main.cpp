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
#include "Engines/Model.hpp"
#include "Engines/Camera.hpp"

int main (int argc, const char * argv[])
{
    Window window (800, 600);
    // Camera
    Camera camera (glm::vec3 (0.0f, 5.0f, 10.0f));
    
    Loader::LoadShader (SHADER_FULL_DIR"model.vs", SHADER_FULL_DIR"model.frag", nullptr, "model");
    
    // Load nanosuit using our model loader
    Model mountain (MODEL_FULL_DIR"nanosuit/nanosuit.obj");
    
    glEnable (GL_DEPTH_TEST);
    
    while (!window.IsClose ())
    {
        window.CalcDeltaTime ();
        
        window.Clear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Input::SetDefalutInputs ();
        
        window.PullEvents ();
        
        camera.HandleInput (window.GetDeltaTime ());
        
        glm::mat4 model;
        glm::mat4 view = camera.GetViewMatrix ();
        glm::mat4 projection = glm::perspective (
            camera.Zoom, (float) window.GetScreenWidth () / (float) window.GetScreenHeight (), 0.1f, 100.0f);
        
        Loader::GetShader ("model").Use ();
        Loader::GetShader ("model").SetMatrix4 ("model", model).SetMatrix4 ("view", view).SetMatrix4 ("projection", projection);
        
        mountain.Draw (Loader::GetShader("model"));
        
        window.SwapBuffer ();
    }
    
    return 0;
}
