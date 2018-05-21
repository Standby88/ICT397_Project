#include "WorldTerrain.h"

bool WorldTerrain::inbounds(int xpos, int zpos)
{
	return (xpos >= 0 && xpos <= size && zpos >= 0 && zpos <= size);
}
unsigned char WorldTerrain::getHeightColor(int xpos, int zpos)
{
	if (inbounds(xpos, zpos))
	{
		return heights[zpos*size + xpos];
	}
	return 1;
}
float WorldTerrain::getHeight(int xpos, int zpos)
{

	if (inbounds(xpos, zpos))
	{
		return ((float)(heights[(zpos*size) + xpos])*scale.y);
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
	terMesh.drawTerrain(s);
}
void WorldTerrain::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<WorldTerrain, GameObject>("WorldTerrain")
		.addConstructor<void(*) (void)>()
		.addFunction("Draw", &WorldTerrain::Draw)
		.addFunction("SetTerrainVariable", &WorldTerrain::SetTerrainVariable)
		.addFunction("loadHeightfield", &WorldTerrain::loadHeightfield)
		.addFunction("load", &WorldTerrain::load)
		.addFunction("setScallingFactor", &WorldTerrain::setScalingFactor)
		.addFunction("convert", &WorldTerrain::convert)
		.addFunction("getHeightAt", &WorldTerrain::getHeight)
		.addFunction("CreateTerrainRigidBody", &WorldTerrain::CreateTerrainRigidBody)
		.endClass()
		.endNamespace();
}

void WorldTerrain::SetTerrainVariable(std::string tex1, std::string tex2, std::string tex3, std::string tex4)
{

	Vertex temp;
	GLuint TEMPINDEX = 0;

	for (int z = 0; z < getSize(); z++)
	{
		for (int x = 0; x < getSize(); x++)
		{
			temp.TexCoords.x = ((float)x / getSize());
			temp.TexCoords.y = ((float)z / getSize());
			temp.height = (float)getHeightColor(x, z);

			temp.Position.x = ((float)x*scale.x) + objectPos.x;
			temp.Position.y =  (getHeight(x, z)) + objectPos.y;
			temp.Position.z = ((float)(z)*scale.z) + objectPos.z;

			terMesh.vertices.push_back(temp);
			
		}
	}
	TextureManager::GetTextureManager().AddTexture(tex1);
	TextureManager::GetTextureManager().AddTexture(tex2);
	TextureManager::GetTextureManager().AddTexture(tex3);
	TextureManager::GetTextureManager().AddTexture(tex4);
	
	terMesh.terrainTex[0] = TextureManager::GetTextureManager().GetTexture(tex1);
	terMesh.terrainTex[1] = TextureManager::GetTextureManager().GetTexture(tex2);
	terMesh.terrainTex[2] = TextureManager::GetTextureManager().GetTexture(tex3);
	terMesh.terrainTex[3] = TextureManager::GetTextureManager().GetTexture(tex4);
	

	for (int y = 0; y < getSize() - 1; ++y)
	{
		for (int x = 0; x < getSize() - 1; ++x)
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
	CreateTerrainRigidBody();
	
}

bool WorldTerrain::loadHeightfield(std::string filename, const int size)
{
	const char* cfilename = filename.c_str();
	terrainData = RawIMGLoader::loadRaw(cfilename, size);
	this->size = size;
	return true;
}

void WorldTerrain::setScalingFactor(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}


int WorldTerrain::getSize()
{
	return size;
}

void WorldTerrain::CreateTerrainRigidBody()
{
	terrainData = new unsigned char[size * size];
	float total = 0, aveH = 0, maxH = 0, minH = 1000;
	for (int i = 0; i < heights.size(); i++)
	{
		terrainData[i] = heights[i];
		if (maxH < terMesh.vertices[i].Position.y)
		{
			maxH = terMesh.vertices[i].Position.y;
		}
		if (minH > terMesh.vertices[i].Position.y)
		{
			minH = terMesh.vertices[i].Position.y;
		}

	}

	/*std::cout << "minimum height: " << minH << std::endl;
	std::cout << "maximum height: " << maxH << std::endl;*/

	terrainBody = wPhysFac->CreateHeightFieldRigidBody(size, size, terrainData, scale.x, scale.y, scale.z, maxH, minH);

	/*std::cout << "rigidBodyID for WorldTerrain: " << terrainBody->getUserIndex() << std::endl;
	std::cout << "Centrepoint for WorldTerrain: " << terrainBody->getCenterOfMassPosition().getX() << " "
	<< terrainBody->getCenterOfMassPosition().getY() << " "
			<< terrainBody->getCenterOfMassPosition().getZ() << std::endl;*/
}