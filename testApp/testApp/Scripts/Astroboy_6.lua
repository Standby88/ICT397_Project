--asteroid object
--print ("First Environmental Object")
Astronaut_6 = Factory:Create("NPCObj")
Astronaut_6 = test3:convert(Astronaut_6)
Astronaut_6:addModel(astroboy)
--E2:addRigidbody()
x = 7.0
y = 14.0
Astronaut_6:updateObject(x, T1:getHeightAt(x-50.0,y-50.0), y)
Astronaut_6:updateObjectRotation(180.0,0.0, 1.0, 0.0)
--print ("Model finished ")