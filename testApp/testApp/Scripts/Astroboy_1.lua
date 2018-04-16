--asteroid object
--print ("First Environmental Object")
E3 = Factory:Create("EnvironObj")
E3 = test:convert(E3)
E3:addModel(astroboy)
--E2:addRigidbody()
E3:updateObject(4.0, -1.6, 5.0)
--print ("Model finished ")