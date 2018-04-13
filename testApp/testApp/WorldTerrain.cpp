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

	terMesh.setT();
	Vertex temp;
	GLuint TEMPINDEX = 0;
	/*terMesh.indices.push_back(TEMPINDEX);
	temp.Position.x = -100;
	temp.Position.y = 0;
	temp.Position.z = 0;
	temp.TexCoords.x = 0;
	temp.TexCoords.y = 0;
	terMesh.vertices.push_back(temp);

	temp.Position.x = 100;
	temp.Position.y = 0;
	temp.Position.z = 0;
	temp.TexCoords.x = 0;
	temp.TexCoords.y = 1;
	terMesh.vertices.push_back(temp);

	temp.Position.x = 0;
	temp.Position.y = 100;
	temp.Position.z = 0;
	temp.TexCoords.x = 1;
	temp.TexCoords.y = 0;
	terMesh.vertices.push_back(temp);*/
	unsigned char hc;

	for (int z = 0; z < getSize() - 1; z++)
	{
		for (int x = 0; x < getSize() - 1; x++)
		{
			temp.TexCoords.x = ((float)x / getSize());
			temp.TexCoords.y = ((float)z / getSize());
			hc = getHeightColor(x, z);
			hcolor.push_back(hc);
			temp.Position.x = x;//((float)x*scale.x) + objectPos.x;
			temp.Position.y = 0.5;//(getHeight(x, z)) + objectPos.y;
			temp.Position.z = z;//((float)(z)*scale.z) + objectPos.z;
			//temp.Normal = glm::normalize(temp.Position);

			terMesh.vertices.push_back(temp);

			/*TEMPINDEX = 0;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = 1;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = 3;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = 1;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = 4;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = 3;
			terMesh.indices.push_back(TEMPINDEX);*/
			float start = z * getSize() + x;
			TEMPINDEX = start;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + 1;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + getSize();
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start+1;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + getSize();
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + getSize() + 1;
			terMesh.indices.push_back(TEMPINDEX);
		}
	}
	/*int k = 0;
	for (int z = 0; z < getSize() - 1; z++)
	{
		for (int x = 0; x < getSize() - 1; x++)
		{
			float start = z * getSize() + x;
			TEMPINDEX = start;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + 1;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + getSize();
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + 1;
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + 1 + getSize();
			terMesh.indices.push_back(TEMPINDEX);
			TEMPINDEX = start + getSize();
			terMesh.indices.push_back(TEMPINDEX);
		}
	}*/

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