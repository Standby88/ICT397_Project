#include "GraphicsEngine.h"

#include <glm\gtc\type_ptr.hpp>

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::GLFWpro()
{
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	std::cout << "1. GLFW initation complete" << std::endl;

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return false;
	}

	


	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	std::cout << "2. Window context creation complete" << std::endl;

	camera = Camera(glm::vec3(50.0f, 90.0f, 250.0f));

	// Set the required callback functions
	//PlayerInput playerInput = PlayerInput(WIDTH, HEIGHT, &camera, &deltaTime);
	//PlayerInput playerInput = PlayerInput::getCurrentPlayerInput();
	//playerInput.SetAttributes(&camera);
	//playerInput.SetCallbacks();

	//glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	std::cout << "3. Input - keyboard complete" << std::endl << "4. Input - mouse complete" << std::endl;

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	LuaEn->doLuaScript("Game.lua");
	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	std::cout << "4. Viewport creation complete" << std::endl;

	// Setup and compile our shaders
	Shader Tshader("terrainvertex.vs", "terrainfrag.frag");
	Shader S("3dvsShaderTEMP.vs", "3dfragShaderTEMP.frag");
	
	std::cout << "5. Shader setup and compiled" << std::endl;
	// Load models
	//Model ourModel("nanosuit/nanosuit.obj");
	if (m_Models.addModel("nanosuit/nanosuit.obj"))
	{
		std::cout << "6. nanosuit/nanosuit.obj SUCCESS" << std::endl;
	}
	else
		std::cout << "6. nanosuit/nanosuit.obj FAILED" << std::endl;

	std::cout << "6. Models loaded" << std::endl;

	m_TextureMan = TextureManager::GetTextureManager();
	/**/
	//Model* m = m_Models.GetModel("nanosuit/nanosuit.obj");

	EnvironmentObjManager *Etest = NULL;
	Etest = getGlobal(LuaEn->getLuaState(), "EnObjMan");
	TerrainManager *Ttest = NULL;
	Ttest = getGlobal(LuaEn->getLuaState(), "TerManager");
	//Etest->getObject("N1")->updateObject(50.0, 100.0, 0.0);
	//EnvironmentObject * b = NULL;
	//b = getGlobal(LuaEn->getLuaState(), "Mod1");
	//b->getObjectType();
	//GameAssetFactory<GameObject, std::string> GA;
	//GA.Register("Ter", new GameAssetCreator<WorldTerrain, GameObject>);
	//GA.Register("Nano", new GameAssetCreator<EnvironmentObject, GameObject>);
	//TerrainManager a;
	//a.AddTerrain(GA.Create("Ter"));
	//a.getTerrain(0)->setScalingFactor(5.0f, 0.5f, 1.0f);
	//a.getTerrain(0)->loadHeightfield("height128.raw", 128);
	//a.getTerrain(0)->SetTerrainVariable("images/ice.png", "images/grey.png", "images/pebble.png", "images/dirt.png");
	
	/*EnvironmentObjManager c;
	c.addObject(GA.Create("Nano"), "N1");
	c.addObject(GA.Create("Nano"), "N2");
	c.getObject("N1")->addModel(m_Models.GetModel("nanosuit/nanosuit.obj"));
	c.getObject("N2")->addModel(m_Models.GetModel("nanosuit/nanosuit.obj"));
	c.getObject("N2")->updateObject(50.0f, 10.0f, 0.0f);

	EnvironmentObject * b = NULL;
	b = getGlobal(LuaEn->getLuaState(), "E2");*/
	//b->addModel(m_Models.GetModel("nanosuit/nanosuit.obj"));
	// Draw in wireframe
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();

		//playerInput.DoMovement(deltaTime);

		//playerInputDoMovement(deltaTime);

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		S.Use();
		glm::mat4 view = camera.GetViewMatrix();
		/*glUniformMatrix4fv(glGetUniformLocation(S.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0,0,0)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		*/
		//b->Draw(S);
		//c.getObject("N2")->Draw(S);
		SceneRender::renderEnvironmentObj(*Etest,view, projection, S);
		SceneRender::renderTerrain(*Ttest, view, projection, Tshader);

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}
