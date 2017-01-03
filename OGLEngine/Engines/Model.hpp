//
//  Model.h
//  TutorialAssimp
//
//  Created by 梅宇宸 on 12/3/16.
//  Copyright © 2016 梅宇宸. All rights reserved.
//

#ifndef Model_h
#define Model_h

// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.hpp"
#include "Mesh.hpp"

#define MODEL_FULL_DIR "/Users/meiyuchen/Projects/OGLEngine/OGLEngine/Models/"

GLint TextureFromFile (const char* path, string directory);

class Model
{
public:
    /*  Functions   */
    // Constructor, expects a filepath to a 3D model.
    Model (const GLchar* path);
    
    // Draws the model, and thus all its meshes
    void Draw (Shader shader);
    
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    
private:
    /*  Model Data  */
    string directory;
    
    /*  Functions   */
    // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel (string path);
    
    // Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode (aiNode* node, const aiScene* scene);
    
    Mesh processMesh (aiMesh* mesh, const aiScene* scene);
    
    // Checks all material textures of a given type and loads the textures if they're not loaded yet.
    // The required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures (aiMaterial* mat, aiTextureType type, string typeName);
};

#endif