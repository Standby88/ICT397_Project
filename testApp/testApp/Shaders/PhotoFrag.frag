#version 330 core
in vec2 TextCoord;
out vec4 color;
uniform sampler2D t21;
void main()
{
	color = texture(t21, TextCoord);
}