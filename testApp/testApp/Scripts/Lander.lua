--asteroid object
--print ("First Environmental Object")
E6 = Factory:Create("EnvironObj")
E6 = test:convert(E6)
E6:addModel(lander)
--E2:addRigidbody()
E6:updateObject(2.0, -1.0, -20.0)
--print ("Model finished ")