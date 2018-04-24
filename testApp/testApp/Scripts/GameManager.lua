print ("Game script loaded")

-- Create ModelManager
ModManager = MM.ModelManager();
-- Throw to the Model script which will load
-- all the models into the modelmanager
require "Scripts/ModelScript"

--space_car = ModManager:GetModel("assets/MMSEV/MMSEV.obj")
-- create factory to create objects on gameobjects
Factory = GAF.GameAssetFactory()
test = GA.EnvironmentObject()
test2 = GA.WorldTerrain()
-- declare creators
EOC = GAC.EOCreator()
WTC = GAC.WTCreator()

--EnvironObj specifies an environment Object to be created
Factory:Register("EnvironObj", EOC)
Factory:Register("WorldTerrain", WTC)

require "Scripts/Terrain"

TerManager = TM.TerrainManager()
TerManager:AddTerrain(T1)

require "Scripts/Asteriod_1"
require "Scripts/Asteriod_2"
require "Scripts/Asteriod_3"
require "Scripts/Asteriod_4"
require "Scripts/Asteriod_5"
require "Scripts/Asteriod_6"
require "Scripts/Asteriod_7"
require "Scripts/Asteriod_8"
require "Scripts/Asteriod_9"
require "Scripts/Astroboy_1"
require "Scripts/Astroboy_2"
require "Scripts/Astroboy_3"
require "Scripts/Astroboy_4"
require "Scripts/Astroboy_5"
require "Scripts/Astroboy_6"

EnObjMan = EOM.EnvironmentObjManager()
EnObjMan:addObject(A1, "asteroid_1")
EnObjMan:addObject(A2, "asteroid_2")
EnObjMan:addObject(Astronaut_1, "Astroboy_1")
EnObjMan:addObject(A3, "asteroid_3")
EnObjMan:addObject(A4, "asteroid_4")
EnObjMan:addObject(A5, "asteroid_5")
EnObjMan:addObject(Astronaut_2, "Astroboy_2")
EnObjMan:addObject(Astronaut_3, "Astroboy_3")
EnObjMan:addObject(Astronaut_4, "Astroboy_4")
EnObjMan:addObject(Astronaut_5, "Astroboy_5")
EnObjMan:addObject(Astronaut_6, "Astroboy_6")
EnObjMan:addObject(A6, "asteroid_6")
EnObjMan:addObject(A7, "asteroid_7")
EnObjMan:addObject(A8, "asteroid_8")
EnObjMan:addObject(A9, "asteroid_9")


World = GW.GameWorld(TerManager, EnObjMan)

Scene = SR.SceneRender(World)
Scene:addShader("Shaders/3dvsShaderTEMP.vs", "Shaders/3dfragShaderTEMP.frag", "environment")
Scene:addShader("Shaders/terrainvertex.vs", "Shaders/terrainfrag.frag", "terrain")
Scene:addShader("Shaders/coreImage.vs", "Shaders/coreImage.frag", "menuOption")

print ("Game script end")