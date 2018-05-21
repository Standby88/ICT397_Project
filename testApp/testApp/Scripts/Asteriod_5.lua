--asteroid object
--print ("First Environmental Object")
posX = 0.0
posY = 1.0
posZ = 9.0
A5 = Factory:Create("EnvironObj")
A5 = test:convert(A5)
A5:addModel(asteroid_2)
--a5RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 4.0, posX, posY, posZ, 0.0, 0.0, 0.0)
--A5:SetRigidBody(a5RigidBody)
A5:updateObject(posX, posY, posZ)
A5:updateObjectRotation(45.0,0.0, 1.0, 0.0)
--print ("Model finished ")