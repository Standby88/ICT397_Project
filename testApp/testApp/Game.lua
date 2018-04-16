print ("Game script loaded")
-- Create ModelManager
ModManager = MM.ModelManager();

-- add model to manager
ModManager:addModel("nanosuit/nanosuit.obj")
nanoModel = ModManager:GetModel("nanosuit/nanosuit.obj")
t = ModManager:GetModel("nanosuit/nanosuit.obj")
-- create factory to create objects on gameobjects
Factory = GAF.GameAssetFactory()
test = GA.EnvironmentObject()
test2 = GA.WorldTerrain()
-- declare creators
EOC = GAC.EOCreator()
WTC = GAC.WTCreator()

Factory:Register("E", EOC)
Factory:Register("WT", WTC)

E1 = Factory:Create("E")
E1 = test:convert(E1)
E2 = Factory:Create("E")
E2 = test:convert(E2)
T1 = Factory:Create("WT")
T1 = test2:convert(T1);
E1:addModel(nanoModel)
E2:addModel(t)
E1:updateObject(0.0, 0.0, 0.0)
E2:updateObject(10.0, 0.0, 0.0)

T1:setScallingFactor(5.0, 0.5, 1.0)
T1:updateObject(-50.0, -30.0, 0.0)
T1:loadHeightfield("height128.raw", 128)
T1:SetTerrainVariable("images/ice.png", "images/grey.png", "images/pebble.png", "images/dirt.png")
EnObjMan = EOM.EnvironmentObjManager()
EnObjMan:addObject(E1, "N1")
EnObjMan:addObject(E2, "N2")

TerManager = TM.TerrainManager()
TerManager:AddTerrain(T1)

print ("Game script end")