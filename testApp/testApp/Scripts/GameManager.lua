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

require "Scripts/Asteriod_1"
require "Scripts/Asteriod_2"
require "Scripts/Asteriod_3"
require "Scripts/Asteriod_4"
require "Scripts/Asteriod_5"
require "Scripts/Asteriod_6"
require "Scripts/Asteriod_7"
require "Scripts/Asteriod_8"
require "Scripts/Astroboy_1"
require "Scripts/Astroboy_2"
require "Scripts/Astroboy_3"

T1 = Factory:Create("WorldTerrain")
T1 = test2:convert(T1);
T1:setScallingFactor(5.0, 0.2, 1.0)
T1:updateObject(-50.0, -30.0, 0.0)
T1:loadHeightfield("assets/images/height128.raw", 128)
T1:SetTerrainVariable("assets/images/ice.png", "assets/images/grey.png", "assets/images/pebble.png", "assets/images/dirt.png")
EnObjMan = EOM.EnvironmentObjManager()
EnObjMan:addObject(E1, "asteroid_1")
EnObjMan:addObject(E2, "asteroid_2")
EnObjMan:addObject(E3, "Astroboy_1")
EnObjMan:addObject(E4, "asteroid_3")
EnObjMan:addObject(E5, "asteroid_4")
--EnObjMan:addObject(E6, "lander")
EnObjMan:addObject(E7, "asteroid_5")
EnObjMan:addObject(E8, "Astroboy_2")
EnObjMan:addObject(E9, "Astroboy_3")
EnObjMan:addObject(E10, "asteroid_6")
EnObjMan:addObject(E11, "asteroid_7")
EnObjMan:addObject(E12, "asteroid_8")

TerManager = TM.TerrainManager()
TerManager:AddTerrain(T1)

print ("Game script end")