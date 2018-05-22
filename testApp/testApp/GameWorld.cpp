#include "GameWorld.h"

GameWorld::GameWorld(CharacterManager * cha, TerrainManager * ter, EnvironmentObjManager * en, Skybox * sky)
{
	photo = false;
	manual = false;
	worldDisplay = true;
	mainMenu = false;
	wire = false;
	camera = Camera::GetCameraInstance();
	this->skybox = sky;
	this->characters = cha;
	this->terrain = ter;
	this->environment = en;
}

CharacterManager * GameWorld::getCharacters()
{
	return characters;
}

TerrainManager * GameWorld::getTerrain()
{
	return terrain;
}

EnvironmentObjManager * GameWorld::getEnvironment()
{
	return environment;
}

Skybox * GameWorld::getSkybox()
{
	return skybox;
}


void GameWorld::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GW")
		.beginClass<GameWorld>("GameWorld")
		.addConstructor<void(*) (CharacterManager*,TerrainManager*, EnvironmentObjManager*, Skybox *)>()
		.addFunction("setModels", &GameWorld::setModels)
		.endClass()
		.endNamespace();
}

GameWorld::~GameWorld()
{
	characters = nullptr;
	delete characters;
	terrain = nullptr;
	delete terrain;
	environment = nullptr;
	delete environment;
}

void GameWorld::setManual(bool man)
{
	manual = man;
}

void GameWorld::setPhoto(bool pho)
{
	photo = pho;
}

void GameWorld::setWorldDisplay(bool wor)
{
	worldDisplay = wor;
}

void GameWorld::setWire(bool wir)
{
	wire = wir;
}

void GameWorld::setMainmenu(bool menu)
{
	mainMenu = menu;
}

bool GameWorld::getWire()
{
	return wire;
}

bool GameWorld::getMainMenu()
{
	return mainMenu;
}

bool GameWorld::getManual()
{
	return manual;
}

bool GameWorld::getPhoto()
{
	return photo;
}

bool GameWorld::getWorldDisplay()
{
	return worldDisplay;
}

void GameWorld::setScreenHW(int w, int h)
{
	SCREEN_HEIGHT = h;
	SCREEN_WIDTH = w;
}

int GameWorld::getScreenH()
{
	return SCREEN_HEIGHT;
}
int GameWorld::getScreenW()
{
	return SCREEN_WIDTH;
}
void GameWorld::setView(M4 v)
{
	view = v;
}

void GameWorld::setProjection(M4 p)
{
	projection = p;
}

M4 GameWorld::getView()
{
	return view;
}

M4 GameWorld::getProjection()
{
	return projection;
}