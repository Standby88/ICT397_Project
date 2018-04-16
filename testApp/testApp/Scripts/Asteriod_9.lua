--asteroid object
--print ("First Environmental Object")
A9 = Factory:Create("EnvironObj")
A9 = test:convert(A9)
A9:addModel(asteroid_2)
--E2:addRigidbody()
A9:updateObject(18.0, 0.0, 8.0)
--print ("Model finished ")