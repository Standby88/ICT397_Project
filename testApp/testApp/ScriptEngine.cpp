#include "ScriptEngine.h"

ScriptEngine::~ScriptEngine()
{
	lua_close(MainLuaState); 
}

lua_State* ScriptEngine::getLuaState()
{
	return MainLuaState;
}


void ScriptEngine::errorReport(int a)
{
	if (a != 0)
	{
		std::cerr << "ErrorMessage: " << lua_tostring(MainLuaState, a) << std::endl;
		lua_pop(MainLuaState, 1); 
	}
}

void ScriptEngine::doLuaScript(const char* file)
{
	if (file == NULL)
		return;

	int state = luaL_dofile(MainLuaState, file);
	errorReport(state);
}

void ScriptEngine::expFuncToLua(lua_State * L)
{
	GameAssetFactory<GameObject, std::string>::scriptRegister(L);
	BaseCreator<GameObject>::scriptRegister(L);
	getGlobalNamespace(L)
		.beginNamespace("GAC")
		.deriveClass<GameAssetCreator<WorldTerrain, GameObject>, BaseCreator<GameObject>>("WTCreator")
		.addConstructor<void(*) (void)>()
		.addFunction("Create", &GameAssetCreator<WorldTerrain, GameObject>::Create)
		.endClass()
		.deriveClass<GameAssetCreator<EnvironmentObject, GameObject>, BaseCreator<GameObject>>("EOCreator")
		.addConstructor<void(*) (void)>()
		.addFunction("Create", &GameAssetCreator<EnvironmentObject, GameObject>::Create)
		.endClass()
		.deriveClass<GameAssetCreator<Player, GameObject>, BaseCreator<GameObject>>("PCreator")
		.addConstructor<void(*) (void)>()
		.addFunction("Create", &GameAssetCreator<Player, GameObject>::Create)
		.endClass()
		.deriveClass<GameAssetCreator<NPC, GameObject>, BaseCreator<GameObject>>("NPCCreator")
		.addConstructor<void(*) (void)>()
		.addFunction("Create", &GameAssetCreator<NPC, GameObject>::Create)
		.endClass()
		.endNamespace();

	TerrainManager::scriptRegister(L);
	EnvironmentObjManager::scriptRegister(L);
	CharacterManager::scriptRegister(L);
	ModelManager::scriptRegister(L);
	Skybox::scriptRegister(L);

	GameObject::scriptRegister(L);
	GameObject3D::scriptRegister(L);
	Player::scriptRegister(L);
	WorldTerrain::scriptRegister(L);
	EnvironmentObject::scriptRegister(L);
	NPC::scriptRegister(L);
	Model::scriptRegister(L);
	Shader::scriptRegister(L);
	GameWorld::scriptRegister(L);
	SceneRender::scriptRegister(L);
	PhysicsFacade::scriptRegister(L);
	
}