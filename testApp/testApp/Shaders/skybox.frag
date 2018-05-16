#version 330 core
in vec3 TexCoords;

out vec4 color;

// Texture samplers
uniform samplerCube skybox;

void main()
{
    
    color = texture(skybox, TexCoords);
}