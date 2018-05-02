#include "GameEngine.h"

GameEngine::GameEngine()
{
	initialize();
}

bool GameEngine::GameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gameController->update(deltaTime);
		render->renderScene();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return true;
}

void GameEngine::initialize()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Space Dust", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	LuaEn->doLuaScript("Scripts/GameManager.lua");
	gameWorld = getGlobal(LuaEn->getLuaState(), "World");
	gameWorld->setScreenHW(SCREEN_WIDTH, SCREEN_HEIGHT);
	render = getGlobal(LuaEn->getLuaState(), "Scene");
	gameController = new GameController(gameWorld);
	gameController->saveGame();
	PhysFac->SetObjectActivation();
}

GameEngine::~GameEngine()
{
	gameWorld = nullptr;
	delete gameWorld;
	render = nullptr;
	delete render;
	window = nullptr;
	delete window;
	gameController = nullptr;
	delete gameController;
}
