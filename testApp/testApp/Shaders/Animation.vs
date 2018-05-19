#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 4) in vec4 BoneID;
layout (location = 5) in vec4 weight;
out vec2 TexCoords;
out vec4 we;
out vec4 id;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords = texCoords;
	we = weight;
	id = BoneID;
}