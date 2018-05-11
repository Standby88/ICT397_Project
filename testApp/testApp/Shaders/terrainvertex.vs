#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in float height;
out vec2 TexCoords;
out float Height;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
const vec4 plane = vec4(0,-1,0,10);
void main()
{
	//gl_ClipDistance[0] = 60;
	//gl_ClipDistance[1] = 1;
	//gl_ClipDistance[2] = -15;
    gl_Position = projection * view * model * vec4(position, 1.0f);
	
    TexCoords = texCoords;
	Height = height;
}

