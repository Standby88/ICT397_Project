#version 330 core
in vec3 ourColor;
in vec4 clipSpace;
in vec2 texC;
out vec4 color;

// Texture samplers
uniform sampler2D reflectTex;
uniform sampler2D refractTex;
uniform sampler2D dudvTex;

void main()
{
	vec2 textureC = vec2(texC.x / 2.0 + 0.5, texC.y/2.0 + 0.5);
	
	vec3 ndc = (clipSpace.xyz / clipSpace.w)/ 2.0 + 0.5;
	
	vec2 reflectTexCoords = vec2(ndc.x, 1-ndc.y);
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	
	vec2 distortion1 = (texture2D(dudvTex, vec2(textureC.x, textureC.y)).rg*2.0 - 1.0);
	//reflectTexCoords += distortion1;
	//refractTexCoords += distortion1;
	
	vec4 reflect = texture2D(reflectTex, reflectTexCoords);
	vec4 refract = texture2D(reflectTex, refractTexCoords);
	
    color = mix(reflect,refract,0.5);
}