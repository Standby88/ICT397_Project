--asteroid object
--print ("First Environmental Object")
E8 = Factory:Create("EnvironObj")
E8 = test:convert(E8)
E8:addModel(astroboy)
--E2:addRigidbody()
E8:updateObject(8.0, -1.6, 5.0)
E8:updateObjectRotation(88.0,0.0, 1.0, 0.0)
--print ("Model finished ")