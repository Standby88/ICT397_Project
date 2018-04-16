--asteroid object
--print ("First Environmental Object")
A4 = Factory:Create("EnvironObj")
A4 = test:convert(A4)
A4:addModel(asteroid_2)
--E2:addRigidbody()
A4:updateObject(15.0, 0.0, 11.0)
--print ("Model finished ")