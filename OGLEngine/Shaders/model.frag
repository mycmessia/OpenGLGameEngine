#version 330 core

uniform sampler2D texture1;

in vec2 TexCoord;
in vec4 vertexColor;

out vec4 color;

void main ()
{
    color = vertexColor;
}