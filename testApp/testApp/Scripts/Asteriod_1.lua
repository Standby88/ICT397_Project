--asteroid object
--print ("First Environmental Object")
E1 = Factory:Create("EnvironObj")
E1 = test:convert(E1)
E1:addModel(asteroid_1)
--E1:addRigidbody()
E1:updateObject(0.0, 0.0, 0.0)
--print ("Model finished ")