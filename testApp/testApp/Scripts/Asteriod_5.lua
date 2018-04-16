--asteroid object
--print ("First Environmental Object")
A5 = Factory:Create("EnvironObj")
A5 = test:convert(A5)
A5:addModel(asteroid_2)
--E1:addRigidbody()
A5:updateObject(0.0, 0.0, 9.0)
A5:updateObjectRotation(45.0,0.0, 1.0, 0.0)
--print ("Model finished ")