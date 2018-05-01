--asteroid object
--print ("First Environmental Object")
posX = 22.0
posY = 0.0
posZ = 1.0
A8 = Factory:Create("EnvironObj")
A8 = test:convert(A8)
A8:addModel(asteroid_2)
--a8RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 0.0, posX, posY, posZ, 0.0, 0.0, 0.0)
--A8:SetRigidBody(a8RigidBody)
A8:updateObject(posX, posY, posZ)
--print ("Model finished ")