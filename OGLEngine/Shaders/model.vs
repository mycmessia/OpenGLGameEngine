#version 330 core

layout (location = 0) in vec3 position;
//layout (loaciton = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec4 vertexColor;

void main ()
{
    gl_Position = projection * view * model * vec4 (position, 1.0f);
    TexCoord = texCoord;
    vertexColor = color;
}