--asteroid object
--print ("First Environmental Object")
T1 = Factory:Create("WorldTerrain")
T1 = test2:convert(T1);
T1:setScallingFactor(8.0, 0.2, 8.0)
T1:updateObject(-50.0, -12.0, -50.0)
T1:loadHeightfield("assets/images/height128.raw", 128)
T1:SetTerrainVariable("assets/images/ice.png", "assets/images/grey.png", "assets/images/pebble.png", "assets/images/dirt.png")
--print ("Model finished ")