
Astronaut_3 = Factory:Create("NPCObj")
Astronaut_3 = test3:convert(Astronaut_3)
Astronaut_3:addModel(astroboy)
--E2:addRigidbody()
Astronaut_3:updateObject(4.0, 0.0, 12.0)
Astronaut_3:updateObjectRotation(12.0,0.0, 1.0, 0.0)
--print ("Model finished ")