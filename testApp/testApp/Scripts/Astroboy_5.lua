--asteroid object
--print ("First Environmental Object")
Astronaut_5 = Factory:Create("EnvironObj")
Astronaut_5 = test:convert(Astronaut_5)
Astronaut_5:addModel(astroboy)
--E2:addRigidbody()
x = -3.0
y = -4.0
Astronaut_5:updateObject(x, T1:getHeightAt(x-50.0,y-50.0), y)
Astronaut_5:updateObjectRotation(120.0,0.0, 1.0, 0.0)
--print ("Model finished ")