

T1 = Factory:Create("WorldTerrain")
T1 = test2:convert(T1);
T1:setScallingFactor(2.0, 2.0, 2.0)
--don't need to translate mesh, rigidbody moves to mesh now
--T1:updateObject(0.0, -100.0, 0.0)
print ("terrain")
T1:load("assets/images/hf100.bmp", 100)
T1:SetTerrainVariable("assets/images/ice.png", "assets/images/grey.png", "assets/images/pebble.png", "assets/images/dirt.png")
--print ("Model finished ")