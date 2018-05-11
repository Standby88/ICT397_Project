#include "GameEngine.h"
#include "WaterFrameBuffer.h"
#include "Water.h"
GameEngine::GameEngine()
{
	initialize();
}

bool GameEngine::GameLoop()
{
	//WaterFrameBuffer fbos;

	/*
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;



	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	//generate name for frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//create the framebuffer
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//indicate that we will always render to color attachment 0

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 320, 180, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,texture, 0);
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 320, 180);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);*/

	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	//Water test(fbos.getReflectionTexture(), fbos.getRefractionTexture());
	//render->addWater(&test);
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		gameController->update(deltaTime);
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render->renderScene();
		//glEnable(GL_CLIP_DISTANCE0);
		//glEnable(GL_CLIP_DISTANCE2);
		//glEnable(GL_CLIP_DISTANCE1);
		/*fbos.bindReflectionFrameBuffer();
		
		float distance = 2 * (gameController->getGameCamera()->GetCameraPosition().y - 0.1);
		gameController->getGameCamera()->GetCameraPosition().y -= distance;
		gameController->getGameCamera()->getPitch() = -gameController->getGameCamera()->getPitch();
		render->renderScene();
		gameController->getGameCamera()->GetCameraPosition().y += distance;
		gameController->getGameCamera()->getPitch() = -gameController->getGameCamera()->getPitch();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		fbos.bindRefractionFrameBuffer();
		render->renderScene();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);*/

		
		//render->renderWater();
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
	//gameController->loadGame();
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
