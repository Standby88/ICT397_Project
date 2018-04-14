#include "WorldTerrain.h"
#include <iostream>
bool WorldTerrain::inbounds(int xpos, int zpos)
{
	return (xpos >= 0 && xpos <= size && zpos >= 0 && zpos <= size);
}
unsigned char WorldTerrain::getHeightColor(int xpos, int zpos)
{
	if (inbounds(xpos, zpos))
	{
		return terrainData[zpos*size + xpos];
	}
	return 1;
}
float WorldTerrain::getHeight(int xpos, int zpos)
{

	if (inbounds(xpos, zpos))
	{
		return ((float)(terrainData[(zpos*size) + xpos])*scale.y);
	}

	return 0;
}
WorldTerrain::WorldTerrain()
{
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	terrainData = NULL;
}

WorldTerrain::~WorldTerrain()
{

}

void WorldTerrain::Draw(Shader s)
{
	terMesh.Draw(s);
}
void WorldTerrain::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<WorldTerrain, GameObject>("WorldTerrain")
		.addConstructor<void(*) (void)>()
		.addFunction("Draw", &WorldTerrain::Draw)
		.endClass()
		.endNamespace();
}

void WorldTerrain::collectData()
{

	Vertex temp;
	GLuint TEMPINDEX = 0;
	
	float hc;

	for (int z = 0; z < getSize(); z++)
	{
		for (int x = 0; x < getSize(); x++)
		{
			temp.TexCoords.x = ((float)x / getSize());
			temp.TexCoords.y = ((float)z / getSize());
			hc = (float)getHeightColor(x, z)/256.0f;
			temp.color.x = hc;
			temp.color.y = hc;
			temp.color.z = hc;
			temp.color.w = 1.0f;
			temp.Position.x = ((float)x*scale.x) + objectPos.x;
			temp.Position.y = (getHeight(x, z)) + objectPos.y;
			temp.Position.z = ((float)(z)*scale.z) + objectPos.z;
			//temp.Normal = glm::normalize(temp.Position);

			terMesh.vertices.push_back(temp);
		}
	}

	for (int y = 0; y < getSize() -1; ++y)
	{
		for (int x = 0; x < getSize() -1; ++x)
		{
				int start = y * getSize() + x;
				terMesh.indices.push_back((short)start);
				terMesh.indices.push_back((short)(start + 1));
				terMesh.indices.push_back((short)(start + getSize()));
				terMesh.indices.push_back((short)(start + 1));
				terMesh.indices.push_back((short)(start + 1 + getSize()));
				terMesh.indices.push_back((short)(start + getSize()));
		}
	}
	
	terMesh.setMesh();
}

bool WorldTerrain::loadHeightfield(char * filename, const int size)
{
	terrainData = RawIMGLoader::loadRaw(filename, size);
	this->size = size;
	return true;
}

void WorldTerrain::setScalingFactor(glm::vec3 newScale)
{
	scale = newScale;
}


int WorldTerrain::getSize()
{
	return size;
}