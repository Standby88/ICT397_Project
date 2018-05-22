#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 texCoords;
layout (location = 4) in ivec4 ids;
layout (location = 5) in vec4 weights;


out vec2 TexCoords;
out vec3 normal;
out vec3 fragPos;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normals_matrix;

const int MAX_BONES = 100;
uniform mat4 bones[MAX_BONES];
void main()
{
	mat4 BMatrix = bones[ids[0]] * weights[0];
         BMatrix += bones[ids[1]] * weights[1];
         BMatrix += bones[ids[2]] * weights[2];
         BMatrix += bones[ids[3]] * weights[3];
		  
	vec4 bonedPosition = BMatrix * vec4(position, 1.0);
	
	normal = normalize(vec3(normals_matrix * (BMatrix * vec4(normal, 0.0))));
	
	fragPos = vec3(model*bonedPosition);
	
    gl_Position = projection * view * model * bonedPosition;
    TexCoords = texCoords;

}