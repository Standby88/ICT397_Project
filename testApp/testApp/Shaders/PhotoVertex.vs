#version 330 core

in vec3 vp;
in vec2 texcoord;
out vec2 TextCoord;

void main() 
{
TextCoord = texcoord;
  gl_Position = vec4(vp, 1.0);
};