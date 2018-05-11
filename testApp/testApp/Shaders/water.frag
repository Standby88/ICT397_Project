#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
void main()
{
	vec4 reflect = texture(ourTexture1, TexCoord);
	vec4 refract = texture(ourTexture1, TexCoord);
    color = mix(refract,reflect, 0.5);
}