#include "GameEngine.h"
#include "WaterFrameBuffer.h"
#include "Water.h"
#include "MathLib.h"
GameEngine::GameEngine()
{
	initialize();
}

bool GameEngine::GameLoop()
{
	gameWorld->getCharacters()->getNPC("Mon1")->skeleton.SetIdleAnimation(&Anim_Test_Idle);
	gameWorld->getCharacters()->getNPC("Mon1")->PlayAnimation(Anim_Test_Idle, true, true);
	while (!window.windowShouldClose())
	{
		GLfloat currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		dt->setDeltaTime(deltaTime);
		gameController->update(deltaTime);
		window.clearBufferNColor();
		render->renderScene();
		window.swapBuffers();
	}

	glfwTerminate();
	return true;
}

void GameEngine::initialize()
{
	SCREEN_WIDTH = window.getScreenWidth();
	SCREEN_HEIGHT = window.getScreenHeight();
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	LuaEn->doLuaScript("Scripts/GameManager.lua");
	gameWorld = getGlobal(LuaEn->getLuaState(), "World");
	gameWorld->setScreenHW(SCREEN_WIDTH, SCREEN_HEIGHT);
	render = getGlobal(LuaEn->getLuaState(), "Scene");
	gameController = new GameController(gameWorld);
	PhysFac->SetObjectActivation();
	dt = FrameTime::getInstance();
	gameWorld->getCharacters()->getNPC("Mon1")->AddAnimation(Anim_Test_Walk);
}

GameEngine::~GameEngine()
{
	gameWorld = nullptr;
	delete gameWorld;
	render = nullptr;
	delete render;
	gameController = nullptr;
	delete gameController;
}
