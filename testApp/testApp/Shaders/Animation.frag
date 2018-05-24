#version 330 core
in vec2 TexCoords;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

uniform sampler2D ourTexture1;
uniform vec3 view_pos;
void main()
{
	vec3 viewDir = normalize(view_pos - fragPos);
	
	//vec4 texColor = texture(ourTexture1,TexCoords);
	//vec4 weightsColor = vec4(we.xyz,1.0);
    color = texture(ourTexture1, TexCoords);
}