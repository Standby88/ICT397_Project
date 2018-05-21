--asteroid object
--print ("First Environmental Object")
posX = 18.0
posY = 0.0
posZ = 8.0
A9 = Factory:Create("EnvironObj")
A9 = test:convert(A9)
A9:addModel(asteroid_2)
a9RigidBody = PhysicsManager:CreateSphereRigidBody(0.30, 10.0, posX, posY, posZ, 0.0, 0.0, 0.0)
A9:SetRigidBody(a9RigidBody)
A9:updateObject(posX, posY, posZ)
--print ("Model finished ")