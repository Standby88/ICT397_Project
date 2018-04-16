#version 330 core
in vec2 TexCoords;
in float Height;
out vec4 color;

uniform sampler2D t1;
uniform sampler2D t2;
uniform sampler2D t3;
uniform sampler2D t4;
void main()
{
	vec4 totalColor;
	vec4 T1 = texture2D(t1, TexCoords);
	vec4 T2 = texture2D(t2, TexCoords);
	vec4 T3 = texture2D(t3, TexCoords);
	vec4 T4 = texture2D(t4, TexCoords);
	float weightt1 = (50.0f - abs(Height - 256.0f))/50.0f;
	if(weightt1>0)
	{
		totalColor.x += T1.x*weightt1;
		totalColor.y += T1.y*weightt1;
		totalColor.z += T1.z*weightt1;
	}
	
	float weightt2 = (75.0f - abs(Height - 200.0f))/75.0f;
	if(weightt2>0)
	{
		totalColor.x += T2.x*weightt2;
		totalColor.y += T2.y*weightt2;
		totalColor.z += T2.z*weightt2;
	}
	float weightt3 = (25.0f - abs(Height - 125.0f))/25.0f;
	if(weightt3>0)
	{
		totalColor.x += T3.x*weightt3;
		totalColor.y += T3.y*weightt3;
		totalColor.z += T3.z*weightt3;
	}
	float weightt4 = (100.0f - abs(Height - 100.0f))/100.0f;
	if(weightt4>0)
	{
		totalColor.x += T4.x*weightt4;
		totalColor.y += T4.y*weightt4;
		totalColor.z += T4.z*weightt4;
	}
	color = totalColor;
}