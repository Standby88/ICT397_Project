#version 330 core
in vec2 TexCoords;
in vec4 inColor;
out vec4 color;

uniform sampler2D ourTexture1;

void main()
{
    color = inColor;
}