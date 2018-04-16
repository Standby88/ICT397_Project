--asteroid object
--print ("First Environmental Object")
Astronaut_1 = Factory:Create("EnvironObj")
Astronaut_1 = test:convert(Astronaut_1)
Astronaut_1:addModel(astroboy)
--E2:addRigidbody()
Astronaut_1:updateObject(4.0, T1:getHeightAt(4.0,5.0)-22.97, 5.0)
--print ("Model finished ")