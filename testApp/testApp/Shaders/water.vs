#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec4 clipSpace;
out vec2 texC;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const float tiling = 6.0;
void main()
{
	clipSpace = projection * view*model * vec4(position, 1.0f);
    gl_Position = clipSpace;
    ourColor = color;
	texC = texCoord;
}