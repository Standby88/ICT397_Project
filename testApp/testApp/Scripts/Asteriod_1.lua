--asteroid object
--print ("First Environmental Object")
A1 = Factory:Create("EnvironObj")
A1 = test:convert(A1)
A1:addModel(asteroid_1)
--A1:addRigidbody()
A1:updateObject(0.0, 2.2, 0.0)
--print ("Model finished ")
--print(T1:getHeightAt(0.0,0.0))