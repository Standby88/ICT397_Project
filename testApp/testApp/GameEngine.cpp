#include "GameEngine.h"

#include <glm\gtc\type_ptr.hpp>
GameEngine::GameEngine()
{
	initilize();
}

bool GameEngine::GameLoop()
{
	
	
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		playerInput.DoMovement(deltaTime);
		
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera = Camera::GetCameraInstance();
		view = camera->GetViewMatrix();
		render->renderScene(view, projection);

		/*if (PlayerInput::getCurrentPlayerInput().photo == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			PlayerInput::getCurrentPlayerInput().wire = true;

			drawPhoto(Pshader);
		}
		if (PlayerInput::getCurrentPlayerInput().Manual == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			PlayerInput::getCurrentPlayerInput().wire = true;

			drawMaunal(Pshader);
		}
		if (PlayerInput::getCurrentPlayerInput().wire == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}*/
		
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return true;
}

void GameEngine::initilize()
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
	
	camera = Camera::GetCameraInstance();
	projection = glm::perspective(camera->GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);


	playerInput = PlayerInput::getCurrentPlayerInput();
	playerInput.SetAttributes(camera);
	playerInput.SetCallbacks();
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	LuaEn->doLuaScript("Scripts/GameManager.lua");
	gameWorld = getGlobal(LuaEn->getLuaState(), "World");

	render = getGlobal(LuaEn->getLuaState(), "Scene");
}


GameEngine::~GameEngine()
{
}
