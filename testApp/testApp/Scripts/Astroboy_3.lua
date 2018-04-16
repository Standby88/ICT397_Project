--asteroid object
--print ("First Environmental Object")
E9 = Factory:Create("EnvironObj")
E9 = test:convert(E9)
E9:addModel(astroboy)
--E2:addRigidbody()
E9:updateObject(4.0, -1.6, 12.0)
E9:updateObjectRotation(12.0,0.0, 1.0, 0.0)
--print ("Model finished ")