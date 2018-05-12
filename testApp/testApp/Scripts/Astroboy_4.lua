--asteroid object
--print ("First Environmental Object")
Astronaut_4 = Factory:Create("NPCObj")
Astronaut_4 = test3:convert(Astronaut_4)
Astronaut_4:addModel(astroboy)
--E2:addRigidbody()
x = 12.0
y = -5.0
Astronaut_4:updateObject(x, T1:getHeightAt(x-50.0,y-50.0), y)
Astronaut_4:updateObjectRotation(270.0,0.0, 1.0, 0.0)
--print ("Model finished ")