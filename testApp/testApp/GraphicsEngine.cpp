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

	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	PlayerInput playerInput = PlayerInput::getCurrentPlayerInput();
	playerInput.SetAttributes(&camera);
	playerInput.SetCallbacks();


	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	std::cout << "3. Input - keyboard complete" << std::endl << "4. Input - mouse complete" << std::endl;

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

	std::cout << "4. Viewport creation complete" << std::endl;

	// Setup and compile our shaders
	Shader Tshader("Shaders/terrainvertex.vs", "Shaders/terrainfrag.frag");
	Shader S("Shaders/3dvsShaderTEMP.vs", "Shaders/3dfragShaderTEMP.frag");
	Shader Pshader("Shaders/coreImage.vs","Shaders/coreImage.frag");

	//extents position of the window

	EnvironmentObjManager *Etest = NULL;
	Etest = getGlobal(LuaEn->getLuaState(), "EnObjMan");
	TerrainManager *Ttest = NULL;
	Ttest = getGlobal(LuaEn->getLuaState(), "TerManager");

	// Draw in wireframe
	//

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
		playerInput.DoMovement(deltaTime);
		
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera = Camera::getCameraInstance();
		glm::mat4 view = camera.GetViewMatrix();
		SceneRender::renderEnvironmentObj(*Etest,view, projection, S);
		SceneRender::renderTerrain(*Ttest, view, projection, Tshader);

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

void GraphicsEngine::setupPhoto()
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

void GraphicsEngine::drawPhoto(Shader S)
{
	S.Use();
	glUniform1i(glGetUniformLocation(S.Program, "texture1"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); 
}

GraphicsEngine::~GraphicsEngine()
{
}
