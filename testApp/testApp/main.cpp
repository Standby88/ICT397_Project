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

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
int main()
{
	
	GraphicsEngine grap;
	if (grap.GLFWpro() == true)
	{
		return 1;
	}


	return 0;
}