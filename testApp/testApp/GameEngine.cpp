#include "GameEngine.h"

#include <glm\gtc\type_ptr.hpp>
GameEngine::GameEngine()
{

}

bool GameEngine::GLFWpro()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	Shader Pshader("Shaders/coreImage.vs","Shaders/coreImage.frag");

	initilize();

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

void GameEngine::initilize()
{
	camera = Camera::GetCameraInstance();
	playerInput = PlayerInput::getCurrentPlayerInput();
	playerInput.SetAttributes(camera);
	playerInput.SetCallbacks();
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	LuaEn->doLuaScript("Scripts/GameManager.lua");
	gameWorld = getGlobal(LuaEn->getLuaState(), "World");
	render = new SceneRender(gameWorld);
	projection = glm::perspective(camera->GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	render->addShader("Shaders/3dvsShaderTEMP.vs", "Shaders/3dfragShaderTEMP.frag", "environment");
	render->addShader("Shaders/terrainvertex.vs", "Shaders/terrainfrag.frag", "terrain");
	setupPhoto();
	setUpmanual();
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
