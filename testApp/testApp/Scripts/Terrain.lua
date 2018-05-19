

T1 = Factory:Create("WorldTerrain")
T1 = test2:convert(T1);
T1:setScallingFactor(1.0, 1.0, 1.0)
T1:updateObject(0.0, -100.0, 0.0)
print ("terrain")
T1:load("assets/images/hf100.bmp", 100)
T1:SetTerrainVariable("assets/images/ice.png", "assets/images/grey.png", "assets/images/pebble.png", "assets/images/dirt.png")
--print ("Model finished ")