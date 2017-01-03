//
//  Mesh.h
//
//
//  Created by 梅宇宸 on 12/3/16.
//
//

#ifndef Mesh_h
#define Mesh_h

// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.hpp"

using namespace std;

struct Vertex {
    // Position
    glm::vec3 Position;
    
    // Normal
    glm::vec3 Normal;
    
    // TexCoords
    glm::vec2 TexCoords;
    
    // Colors
    glm::vec4 Color;
};

struct Texture {
    GLuint id;
    string type;
    aiString path;
};

class Mesh
{
public:
    /*  Mesh Data  */
    vector<Vertex>  vertices;
    vector<GLuint>  indices;
    vector<Texture> textures;
    
    /*  Functions  */
    // Constructor
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    
    // Render the mesh
    void Draw (Shader shader);
    
    GLuint VAO;
    
private:
    /*  Render data  */
    GLuint VBO, EBO;
    
    /*  Functions    */
    // Initializes all the buffer objects/arrays
    void setupMesh ();
};


#endif