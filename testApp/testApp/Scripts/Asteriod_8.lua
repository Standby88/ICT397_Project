--asteroid object
--print ("First Environmental Object")
A8 = Factory:Create("EnvironObj")
A8 = test:convert(A8)
A8:addModel(asteroid_2)
--E2:addRigidbody()
A8:updateObject(22.0, 0.0, 1.0)
--print ("Model finished ")