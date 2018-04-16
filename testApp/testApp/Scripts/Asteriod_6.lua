--asteroid object
--print ("First Environmental Object")
A6 = Factory:Create("EnvironObj")
A6 = test:convert(A6)
A6:addModel(asteroid_1)
--E2:addRigidbody()
A6:updateObject(10.0, -4.0, 0.0)
A6:updateObjectRotation(22.0,1.0,0.0,0.0)
--print ("Model finished ")