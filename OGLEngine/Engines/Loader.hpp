//
//  Loader.hpp
//  GameEngine
//
//  Created by 梅宇宸 on 17/1/2.
//  Copyright © 2017年 梅宇宸. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <map>
#include <vector>

#include "RawModel.hpp"

class Texture2D;
class Shader;

class Loader
{
public:
    ~Loader ();
    
    static RawModel LoadToVAO (float positions[], int positionsLength, int indices[], int indiceslength);
    
    static void CleanUp ();
    
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static void LoadShader (const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    
    // Retrieves a stored sader
    static Shader& GetShader (std::string name);
    
    // Loads (and generates) a texture from file
    static void LoadTexture (const GLchar *file, GLboolean alpha, std::string name);
    
    // Retrieves a stored texture
    static Texture2D& GetTexture (std::string name);
    
private:
    static std::vector<GLuint> vaos;
    static std::vector<GLuint> vbos;
    
    // Resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    
    // Private constructor, that is we do not want any actual Loader objects.
    // Its members and functions should be publicly available (static).
    Loader () {}
    
    static GLuint CreateVAO ();
    
    static void StoreDataInAttributeList (int attrNumber, float data[], int dataLength);
    
    static void UnbindVAO ();
    
    static void BindIndicesBuffer (int indices[], int indicesLength);
    
    // Loads and generates a shader from file
    static Shader LoadShaderFromFile (const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    
    // Loads a single texture from file
    static Texture2D LoadTextureFromFile (const GLchar *file, GLboolean alpha);
};

#endif /* Loader_hpp */
