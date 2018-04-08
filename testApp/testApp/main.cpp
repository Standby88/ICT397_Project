#include <iostream>

#include "GraphicsEngine.h"
#include "GameAssetFactory.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include "CharacterCreator.h"
#include "TerrainCreator.h"
#include "WorldTerrain.h"
#include <string>
int main()
{
	//Register
	GameAssetFactory<Character, std::string> characterMap;
	characterMap.Register("Enemy", new CharacterCreator<Enemy, Character>);
	characterMap.Register("Player", new  CharacterCreator<Player, Character>);
	GameAssetFactory<Terrain, std::string> terrainMap;
	terrainMap.Register("Te1", new TerrainCreator<WorldTerrain, Terrain>);


	//Pointer to base interface
	Character* cha = 0;
	Terrain* Ter = 0;
	//Create and call
	cha = characterMap.Create("Enemy");
	std::string str = cha->getName();
	std::cout << str << std::endl;
	delete cha;

	cha = characterMap.Create("Player");
	str = cha->getName();
	std::cout << str << std::endl;
	delete cha;

	Ter = terrainMap.Create("Te1");
	std::cout << Ter->getID() << std::endl;
	delete ter;
	GraphicsEngine grap;
	if (grap.GLFWpro() == true)
	{
		return 1;
	}


	return 0;
}