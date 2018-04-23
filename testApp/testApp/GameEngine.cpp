#include "GameEngine.h"

#include <glm\gtc\type_ptr.hpp>
GameEngine::GameEngine()
{

}

bool GameEngine::GLFWpro()
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

	//std::cout << "1. GLFW initation complete" << std::endl;

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
	//std::cout << "2. Window context creation complete" << std::endl;
	render = new SceneRender(gameWorld);
	camera = Camera::GetCameraInstance();
	
	PlayerInput playerInput = PlayerInput::getCurrentPlayerInput();
	playerInput.SetAttributes(camera);
	playerInput.SetCallbacks();

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}
	setupPhoto();
	setUpmanual();

	LuaEn->doLuaScript("Scripts/GameManager.lua");

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	//std::cout << "4. Viewport creation complete" << std::endl;

	// Setup and compile our shaders
	Shader Tshader("Shaders/terrainvertex.vs", "Shaders/terrainfrag.frag");
	Shader Pshader("Shaders/coreImage.vs","Shaders/coreImage.frag");
	
	//extents position of the window


	Eom = getGlobal(LuaEn->getLuaState(), "EnObjMan");
	Tm = getGlobal(LuaEn->getLuaState(), "TerManager");

	gameWorld = new GameWorld(Tm, Eom);
	render = new SceneRender(gameWorld);
	glm::mat4 projection = glm::perspective(camera->GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	render->addShader("Shaders/3dvsShaderTEMP.vs", "Shaders/3dfragShaderTEMP.frag", "environment");
	render->addShader("Shaders/terrainvertex.vs", "Shaders/terrainfrag.frag", "terrain");
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
		glm::mat4 view = camera->GetViewMatrix();
		render->renderScene(view, projection);
		//SceneRender::renderTerrain(*Tm, view, projection, Tshader);

		if (PlayerInput::getCurrentPlayerInput().photo == true)
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
		}
		
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return true;
}

void GameEngine::setupPhoto()
{
	GLfloat points[] =
	{
		// Positions          // Colors           // Texture Coords
		1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
	};

	GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	m_TextureMan = TextureManager::GetTextureManager();
	m_TextureMan.AddTexture("assets/images/ICT397.jpg");

	texture1 = m_TextureMan.GetTexture("assets/images/ICT397.jpg");
}

void GameEngine::drawPhoto(Shader S)
{
	S.Use();
	glUniform1i(glGetUniformLocation(S.Program, "texture1"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); 
}

void GameEngine::setUpmanual()
{
	GLfloat points[] =
	{
		// Positions          // Colors           // Texture Coords
		1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
	};

	GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	m_TextureMan = TextureManager::GetTextureManager();
	m_TextureMan.AddTexture("assets/images/manual.png");

	texture2 = m_TextureMan.GetTexture("assets/images/manual.png");
}

void GameEngine::drawMaunal(Shader S)
{
	S.Use();
	glUniform1i(glGetUniformLocation(S.Program, "texture2"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


GameEngine::~GameEngine()
{
}
