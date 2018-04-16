--asteroid object
--print ("First Environmental Object")
E5 = Factory:Create("EnvironObj")
E5 = test:convert(E5)
E5:addModel(asteroid_2)
--E2:addRigidbody()
E5:updateObject(15.0, 0.0, 11.0)
--print ("Model finished ")