//
//  Loader.cpp
//  GameEngine
//
//  Created by 梅宇宸 on 17/1/2.
//  Copyright © 2017年 梅宇宸. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

#include "Texture2D.hpp"
#include "Shader.hpp"
#include "Loader.hpp"

std::vector<GLuint> Loader::vaos;
std::vector<GLuint> Loader::vbos;

// Instantiate static variables
std::map<std::string, Texture2D> Loader::Textures;
std::map<std::string, Shader> Loader::Shaders;

Loader::~Loader ()
{
    CleanUp ();
}

RawModel Loader::LoadToVAO (float positions[], int positionsLength, int indices[], int indiceslength)
{
    GLuint vaoID = CreateVAO ();
    
    vaos.push_back (vaoID);
    
    BindIndicesBuffer (indices, indiceslength);
    
    StoreDataInAttributeList (0, positions, positionsLength);
    
    UnbindVAO ();
    
    return RawModel (vaoID, indiceslength);
}

void Loader::CleanUp ()
{
    for (unsigned i = 0; i < vaos.size (); i++)
    {
        glDeleteVertexArrays (1, &vaos[i]);
    }
    
    for (unsigned i = 0; i < vbos.size (); i++)
    {
        glDeleteBuffers (1, &vbos[i]);
    }
    
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram (iter.second.ID);
    
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures (1, &iter.second.ID);
}

GLuint Loader::CreateVAO ()
{
    GLuint vaoID;
    
    glGenVertexArrays (1, &vaoID);
    glBindVertexArray (vaoID);
    
    return vaoID;
}

void Loader::StoreDataInAttributeList (int attrNumber, float data[], int dataLength)
{
    GLuint vboID;
    
    glGenBuffers (1, &vboID);
    
    vbos.push_back (vboID);
    
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    
        glBufferData (GL_ARRAY_BUFFER, sizeof (float) * dataLength, data, GL_STATIC_DRAW);
        glVertexAttribPointer (attrNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer (GL_ARRAY_BUFFER, 0);
}

void Loader::UnbindVAO ()
{
    glBindVertexArray (0);
}

void Loader::BindIndicesBuffer (int indices[], int indicesLength)
{
    GLuint vboID;
    
    glGenBuffers (1, &vboID);
    
    vbos.push_back (vboID);
    
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vboID);
    
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (int) * indicesLength, indices, GL_STATIC_DRAW);

    // Bind this bufferData to the VAO
    // Can not unbind or the OpenGL can not find it when draw
//    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Loader::LoadShader (const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
    Shaders[name] = LoadShaderFromFile (vShaderFile, fShaderFile, gShaderFile);
}

Shader& Loader::GetShader(std::string name)
{
    return Shaders[name];
}

void Loader::LoadTexture (const GLchar *file, GLboolean alpha, std::string name)
{
    Textures[name] = LoadTextureFromFile (file, alpha);
}

Texture2D& Loader::GetTexture(std::string name)
{
    return Textures[name];
}

Shader Loader::LoadShaderFromFile (const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar*gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile (vShaderFile);
        std::ifstream fragmentShaderFile (fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf ();
        fShaderStream << fragmentShaderFile.rdbuf ();
        
        // close file handlers
        vertexShaderFile.close ();
        fragmentShaderFile.close ();
        
        // Convert stream into string
        vertexCode = vShaderStream.str ();
        fragmentCode = fShaderStream.str ();
        
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile (gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf ();
            geometryShaderFile.close ();
            geometryCode = gShaderStream.str ();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    
    const GLchar *vShaderCode = vertexCode.c_str ();
    const GLchar *fShaderCode = fragmentCode.c_str ();
    const GLchar *gShaderCode = geometryCode.c_str ();
    
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile (vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D Loader::LoadTextureFromFile (const GLchar* file, GLboolean alpha)
{
    // Create Texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    
    // Load image
    int width, height;
    unsigned char* image = SOIL_load_image (
        file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    
    if (image == nullptr)
    {
        std::cout << "ERROR::Load Texture2D " << file << " Failed!" << std::endl;
    }
    
    // Now generate texture
    texture.Generate (width, height, image);
    
    // And finally free image data
    SOIL_free_image_data(image);
    
    return texture;
}