--asteroid object
--print ("First Environmental Object")
posX = 10.0
posY = -4.0
posZ = 0.0
A6 = Factory:Create("EnvironObj")
A6 = test:convert(A6)
A6:addModel(asteroid_1)
--a6RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 0.0, posX, posY, posZ, 0.0, 0.0, 0.0)
--A6:SetRigidBody(a6RigidBody)
A6:updateObject(posX, posY, posZ)
A6:updateObjectRotation(22.0,1.0,0.0,0.0)
--print ("Model finished ")