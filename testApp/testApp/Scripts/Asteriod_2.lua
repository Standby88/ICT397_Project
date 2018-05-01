--asteroid object
--print ("First Environmental Object")
posX = 10.0
posY = 0.0
posZ = 0.0
A2 = Factory:Create("EnvironObj")
A2 = test:convert(A2)
A2:addModel(asteroid_2)
--a2RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 0.0, posX, posY, posZ, 0.0, 0.0, 0.0)
--A2:SetRigidBody(a2RigidBody)
A2:updateObject(posX, posY, posZ)
--print ("Model finished ")