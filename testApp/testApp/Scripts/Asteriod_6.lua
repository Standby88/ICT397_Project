--asteroid object
--print ("First Environmental Object")
E10 = Factory:Create("EnvironObj")
E10 = test:convert(E10)
E10:addModel(asteroid_1)
--E2:addRigidbody()
E10:updateObject(10.0, -4.0, 0.0)
E10:updateObjectRotation(22.0,1.0,0.0,0.0)
--print ("Model finished ")