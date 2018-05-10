print ("Game script loaded")

-- Create Physics Instance
PhysicsManager = PF.PhysicsFacade()

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

EnObjMan = EOM.EnvironmentObjManager()
EnObjMan:addObject(A1, "asteroid_1")



World = GW.GameWorld(TerManager, EnObjMan)
World:setModels(ModManager);
Scene = SR.SceneRender(World)
Scene:addShader("Shaders/3dvsShaderTEMP.vs", "Shaders/3dfragShaderTEMP.frag", "environment")
Scene:addShader("Shaders/terrainvertex.vs", "Shaders/terrainfrag.frag", "terrain")
Scene:addShader("Shaders/coreImage.vs", "Shaders/coreImage.frag", "menuOption")
Scene:addShader("Shaders/water.vs", "Shaders/water.frag", "water")
print ("Game script end")