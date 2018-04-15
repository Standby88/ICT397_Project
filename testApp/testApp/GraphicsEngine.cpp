#include "GraphicsEngine.h"

#include <glm\gtc\type_ptr.hpp>

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::GLFWpro()
{
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	float points[] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.0f, 1.0f, 1.0f
		
	};
	GLuint indices[] =
	{
		0, 1, 2,	
		0, 2, 3		
	};
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

	camera = Camera(glm::vec3(50.0f, 50.0f, 200.0f));
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
	Shader Pshader("PhotoVertex.vs","PhotoFrag.frag");


	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(sizeof(float)*3));

	glBindVertexArray(0);

	m_TextureMan = TextureManager::GetTextureManager();
	TextureManager::GetTextureManager().AddTexture("image/dirt.png");
	texture1 = TextureManager::GetTextureManager().GetTexture("image/dirt.png");

	EnvironmentObjManager *Etest = NULL;
	Etest = getGlobal(LuaEn->getLuaState(), "EnObjMan");
	TerrainManager *Ttest = NULL;
	Ttest = getGlobal(LuaEn->getLuaState(), "TerManager");

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
		glm::mat4 view = camera.GetViewMatrix();
		//SceneRender::renderEnvironmentObj(*Etest,view, projection, S);
		//SceneRender::renderTerrain(*Ttest, view, projection, Tshader);
		
		Pshader.Use();
		GLuint t21 = texture1;
		glUniform1i(glGetUniformLocation(Pshader.Program, "t21"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t21);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}
