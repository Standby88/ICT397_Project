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
	//gl_ClipDistance[0] = dot(position,plane);
	//gl_ClipDistance[1] = 1;
	//gl_ClipDistance[2] = -15;
    gl_Position = projection * view * model * vec4(position, 1.0f);
	
    TexCoords = texCoords;
	Height = height;
}
--EnObjMan:addObject(A2, "asteroid_2")
--EnObjMan:addObject(Astronaut_1, "Astroboy_1")
--EnObjMan:addObject(A3, "asteroid_3")
--EnObjMan:addObject(A4, "asteroid_4")
--EnObjMan:addObject(A5, "asteroid_5")
--EnObjMan:addObject(Astronaut_2, "Astroboy_2")
--EnObjMan:addObject(Astronaut_3, "Astroboy_3")
--EnObjMan:addObject(Astronaut_4, "Astroboy_4")
--EnObjMan:addObject(Astronaut_5, "Astroboy_5")
--EnObjMan:addObject(Astronaut_6, "Astroboy_6")
--EnObjMan:addObject(A6, "asteroid_6")
--EnObjMan:addObject(A7, "asteroid_7")
--EnObjMan:addObject(A8, "asteroid_8")
--EnObjMan:addObject(A9, "asteroid_9")

require "Scripts/Asteriod_2"
require "Scripts/Asteriod_3"
require "Scripts/Asteriod_4"
require "Scripts/Asteriod_5"
require "Scripts/Asteriod_6"
require "Scripts/Asteriod_7"
require "Scripts/Asteriod_8"
require "Scripts/Asteriod_9"
require "Scripts/Astroboy_1"
require "Scripts/Astroboy_2"
require "Scripts/Astroboy_3"
require "Scripts/Astroboy_4"
require "Scripts/Astroboy_5"
require "Scripts/Astroboy_6"
