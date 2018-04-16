--asteroid object
--print ("First Environmental Object")
E2 = Factory:Create("EnvironObj")
E2 = test:convert(E2)
E2:addModel(asteroid_2)
--E2:addRigidbody()
E2:updateObject(10.0, 0.0, 0.0)
--print ("Model finished ")