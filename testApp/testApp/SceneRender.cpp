#include "SceneRender.h"



SceneRender::SceneRender(GameWorld * gw)
{
	gameWorld = gw;
	menu = new Menu();
	water = new Water(fbos.getReflectionTexture(), fbos.getRefractionTexture());
}

void SceneRender::addShader(std::string ver, std::string frag, std::string name)
{
	Shader * s = new Shader(ver, frag);
	typedef std::pair<std::string, Shader*> temp;
	shaders.insert(temp(name, s));
}

SceneRender::~SceneRender()
{
	gameWorld = nullptr;
	delete gameWorld;

	menu = nullptr;
	delete menu;

	std::map<std::string, Shader*>::iterator itr;
	for (itr = shaders.begin(); itr != shaders.end(); ++itr)
	{
		itr->second = nullptr;
		delete itr->second;
	}

}

void SceneRender::renderScene()
{
	if (gameWorld->getWire() == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	if (gameWorld->getWorldDisplay() == false)
	{
		renderMenu(*shaders["menuOption"]);
	}
	else 
	{
		renderWater();
		renderGameScene();
	}
	
}

void SceneRender::renderGameScene()
{
	EnvironmentObjManager *Eom = gameWorld->getEnvironment();
	TerrainManager *Tm = gameWorld->getTerrain();
	CharacterManager *Cm = gameWorld->getCharacters();
	renderCharacters(*Cm, gameWorld->getView(), gameWorld->getProjection(), *shaders["Animation"], *shaders["environment"]);
	renderEnvironmentObj(*Eom, gameWorld->getView(), gameWorld->getProjection(), *shaders["environment"]);
	renderTerrain(*Tm, gameWorld->getView(), gameWorld->getProjection(), *shaders["terrain"]);
}

void SceneRender::renderWater()
{
	fbos.bindReflectionFrameBuffer();
	float distance = 2 * (gameWorld->getCam()->GetCameraPosition().y - 0);
	gameWorld->getCam()->GetCameraPosition().y -= distance;
	gameWorld->getCam()->flipPitch();
	renderGameScene();
	gameWorld->getCam()->GetCameraPosition().y += distance;
	gameWorld->getCam()->flipPitch();
	fbos.unbindCurrentFrameBuffer();

	fbos.bindRefractionFrameBuffer();
	renderGameScene();
	fbos.unbindCurrentFrameBuffer();

	water->drawWater(*shaders["water"], gameWorld->getView(), gameWorld->getProjection());

}
void SceneRender::renderEnvironmentObj(EnvironmentObjManager& EM, M4 view, M4 projection, Shader &S)
{
	std::unordered_map<std::string, EnvironmentObject* > drawMap = EM.getEnObjMap();
	V3 posVec;
	V3 rotateAxis;
	float angle;

	S.Use();
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "projection"), 1, GL_FALSE, MathLib::value_ptr<const float *>(projection));
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "view"), 1, GL_FALSE, MathLib::value_ptr<const float *>(view));
	std::unordered_map<std::string, EnvironmentObject* >::iterator itr;
	int i = 0;
	for (itr = drawMap.begin(); itr != drawMap.end(); ++itr)
	{
		M4 model;
		posVec = (*itr).second->getObjectPos();
		angle = (*itr).second->getObjectAngle();
		rotateAxis = (*itr).second->getObjectRotation();
		if (angle > 0.0f)
			model = MathLib::rotate(model, angle, rotateAxis);
		model = MathLib::translate(model, posVec); // Translate it down a bit so it's at the center of the scene
		model = MathLib::scale(model, V3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "model"), 1, GL_FALSE, MathLib::value_ptr<const float *>(model));
		(*itr).second->Draw(S);
	}
}

void SceneRender::renderTerrain(TerrainManager & TM, M4 view, M4 projection, Shader & S)
{
	std::vector<WorldTerrain*> Tlist = TM.getTerrainList();
	V3 posVec;
	S.Use();
	M4 model;
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "projection"), 1, GL_FALSE, MathLib::value_ptr<const float *>(projection));
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "view"), 1, GL_FALSE, MathLib::value_ptr<const float *>(view));
	std::vector<WorldTerrain*>::iterator itr;
	for (itr = Tlist.begin(); itr != Tlist.end(); ++itr)
	{
		posVec = (*itr)->getObjectPos();
		// Draw the loaded model
		model = MathLib::scale(model, V3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "model"), 1, GL_FALSE, MathLib::value_ptr<const float *>(model));
		(*itr)->Draw(S);
	}
}

void SceneRender::renderMenu(Shader& s)
{
	if (gameWorld->getManual() == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		menu->drawMaunal(s);
	}
	else 
	if (gameWorld->getPhoto() == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		menu->drawPhoto(s);
	}
	
}

void SceneRender::renderCharacters(CharacterManager & TM, M4 view, M4 projection, Shader & animation, Shader & deflt)
{

	std::unordered_map<std::string, NPC* > drawMap = TM.getCharMap();
	V3 posVec;
	V3 rotateAxis;
	float angle;
	Shader* active;
	
	std::unordered_map<std::string, NPC* >::iterator itr;
	for (itr = drawMap.begin(); itr != drawMap.end(); ++itr)
	{
		if ((*itr).second->anim == true)
		{
			active = &animation;
		}
		else
		{
			active = &deflt;
		}
		active->Use();
		glUniformMatrix4fv(glGetUniformLocation(active->Program, "projection"), 1, GL_FALSE, MathLib::value_ptr<const float *>(projection));
		glUniformMatrix4fv(glGetUniformLocation(active->Program, "view"), 1, GL_FALSE, MathLib::value_ptr<const float *>(view));
		M4 model;
		posVec = (*itr).second->getObjectPos();
		angle = (*itr).second->getObjectAngle();
		rotateAxis = (*itr).second->getObjectRotation();
		if (angle > 0.0f)
			model = MathLib::rotate(model, angle, rotateAxis);
		model = MathLib::translate(model, posVec); // Translate it down a bit so it's at the center of the scene
		model = MathLib::scale(model, V3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(active->Program, "model"), 1, GL_FALSE, MathLib::value_ptr<const float *>(model));
		(*itr).second->Draw(*active);
	}
}

void SceneRender::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("SR")
		.beginClass<SceneRender>("SceneRender")
		.addConstructor<void(*) (GameWorld*)>()
		.addFunction("addShader", &SceneRender::addShader)
		.endClass()
		.endNamespace();
}
