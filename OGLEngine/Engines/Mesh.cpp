//
//  Mesh.cpp
//  GameEngine
//
//  Created by 梅宇宸 on 17/1/3.
//  Copyright © 2017年 梅宇宸. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh (vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    // Now that we have all the required data, set the vertex buffers and its attribute pointers.
    this->setupMesh();
}

void Mesh::Draw (Shader shader)
{
    // Bind appropriate textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    GLuint reflectionNr = 1;
    
    for(GLuint i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
        // Retrieve texture number (the N in diffuse_textureN)
        stringstream ss;
        string number;
        string name = this->textures[i].type;
        if(name == "texture_diffuse")
            ss << diffuseNr++; // Transfer GLuint to stream
        else if(name == "texture_specular")
            ss << specularNr++; // Transfer GLuint to stream
        else if(name == "texture_reflection")	// We'll now also need to add the code to set and bind to reflection textures
            ss << reflectionNr++;
        number = ss.str();
        // Now set the sampler to the correct texture unit
        shader.SetInteger ((name + number).c_str(), i);
        
        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0); // Always good practice to set everything back to defaults once configured.
    
    // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
    //glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);
    
    // Draw mesh
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh ()
{
    // Create buffers/arrays
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
    
    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    
    // Vertex Color
    glEnableVertexAttribArray (3);
    glVertexAttribPointer (3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
    
    glBindVertexArray(0);
}