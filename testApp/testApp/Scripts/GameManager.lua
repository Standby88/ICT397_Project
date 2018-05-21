print ("Game script loaded")

-- Create Physics Instance
PhysicsManager = PF.PhysicsFacade()

-- Create ModelManager
ModManager = MM.ModelManager();
-- Throw to the Model script which will load
-- all the models into the modelmanager
require "Scripts/ModelScript"


-- create factory to create objects on gameobjects
Factory = GAF.GameAssetFactory()
test = GA.EnvironmentObject()
test2 = GA.WorldTerrain()
test3 = GA.NPC()

-- declare creators
EOC = GAC.EOCreator()
WTC = GAC.WTCreator()
NPCC = GAC.NPCCreator()

--EnvironObj specifies an environment Object to be created
Factory:Register("EnvironObj", EOC)
Factory:Register("WorldTerrain", WTC)
Factory:Register("NPCObj", NPCC)

require "Scripts/Terrain"

TerManager = TM.TerrainManager()
TerManager:AddTerrain(T1)


--require "Scripts/Asteriod_1"
--require "Scripts/Asteriod_2"
--require "Scripts/Asteriod_3"
--require "Scripts/Asteriod_4"
--require "Scripts/Asteriod_5"
--require "Scripts/Asteriod_6"
--require "Scripts/Asteriod_7"
--require "Scripts/Asteriod_8"
--require "Scripts/Asteriod_9"
--require "Scripts/Astroboy_1"
--require "Scripts/Astroboy_2"
--require "Scripts/Astroboy_3"
--require "Scripts/Astroboy_4"
--require "Scripts/Astroboy_5"
--require "Scripts/Astroboy_6"
require "Scripts/Monster"

EnObjMan = EOM.EnvironmentObjManager()
--EnObjMan:addObject(A1, "asteroid_1")
--EnObjMan:addObject(A2, "asteroid_2")
--EnObjMan:addObject(A3, "asteroid_3")
--EnObjMan:addObject(A4, "asteroid_4")
--EnObjMan:addObject(A5, "asteroid_5")
--EnObjMan:addObject(A6, "asteroid_6")
--EnObjMan:addObject(A7, "asteroid_7")
--EnObjMan:addObject(A8, "asteroid_8")
--EnObjMan:addObject(A9, "asteroid_9")

CharacterMan = CM.CharacterManager()
--CharacterMan:addNPC(Astronaut_1, "Astroboy_1")
--CharacterMan:addNPC(Astronaut_2, "Astroboy_2")
--CharacterMan:addNPC(Astronaut_3, "Astroboy_3")
--CharacterMan:addNPC(Astronaut_4, "Astroboy_4")
--CharacterMan:addNPC(Astronaut_5, "Astroboy_5")
--CharacterMan:addNPC(Astronaut_6, "Astroboy_6")
CharacterMan:addNPC(Monster, "Mon1")

sky = SKY.skybox()
sky:AddSkyboxPath("assets/skybox/indigo_rt.jpg")
sky:AddSkyboxPath("assets/skybox/indigo_lf2.jpg")
sky:AddSkyboxPath("assets/skybox/indigo_up.jpg")
sky:AddSkyboxPath("assets/skybox/indigo_dn.jpg")
sky:AddSkyboxPath("assets/skybox/indigo_bk.jpg")
sky:AddSkyboxPath("assets/skybox/indigo_ft.jpg")

sky:GenSkybox()

World = GW.GameWorld(CharacterMan,TerManager, EnObjMan, sky)
World:setModels(ModManager);
Scene = SR.SceneRender(World)
print ("en")
Scene:addShader("Shaders/3dvsShaderTEMP.vs", "Shaders/3dfragShaderTEMP.frag", "environment")
print ("ter")
Scene:addShader("Shaders/terrainvertex.vs", "Shaders/terrainfrag.frag", "terrain")
print ("core/water")
Scene:addShader("Shaders/coreImage.vs", "Shaders/coreImage.frag", "menuOption")
Scene:addShader("Shaders/water.vs", "Shaders/water.frag", "water")
print ("ani")
Scene:addShader("Shaders/Animation.vs", "Shaders/Animation.frag", "Animation")
Scene:addShader("Shaders/skybox.vs", "Shaders/skybox.frag", "skybox")
print ("Game script end")