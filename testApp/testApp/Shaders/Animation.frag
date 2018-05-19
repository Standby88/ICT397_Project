#version 330 core
in vec2 TexCoords;
in vec4 we;
in vec4 id;
out vec4 color;

uniform sampler2D ourTexture1;

void main()
{
	//vec4 texColor = texture(ourTexture1,TexCoords);
	vec4 weightsColor = vec4(we.xyz,1.0);
    color = weightsColor;//texture(ourTexture1, TexCoords);
}