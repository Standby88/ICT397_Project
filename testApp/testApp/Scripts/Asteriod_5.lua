--asteroid object
--print ("First Environmental Object")
E7 = Factory:Create("EnvironObj")
E7 = test:convert(E7)
E7:addModel(asteroid_2)
--E1:addRigidbody()
E7:updateObject(0.0, 0.0, 9.0)
E7:updateObjectRotation(45.0,0.0, 1.0, 0.0)
--print ("Model finished ")