--asteroid object
--print ("First Environmental Object")
A2 = Factory:Create("EnvironObj")
A2 = test:convert(A2)
A2:addModel(asteroid_2)
--A2:addRigidbody()
A2:updateObject(10.0, 0.0, 0.0)
--print ("Model finished ")