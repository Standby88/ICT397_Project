
Astronaut_2 = Factory:Create("NPCObj")
Astronaut_2 = test3:convert(Astronaut_2)
Astronaut_2:addModel(astroboy)
--E2:addRigidbody()
Astronaut_2:updateObject(8.0, T1:getHeightAt(8.0,5.0)-22.97, 5.0)
Astronaut_2:updateObjectRotation(88.0,0.0, 1.0, 0.0)
--print ("Model finished ")