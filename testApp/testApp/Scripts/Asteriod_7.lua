--asteroid object
--print ("First Environmental Object")
posX = math.random(11.0, 15.0)
posY = 0.0
posZ = math.random(16.0, 18.0)
A7 = Factory:Create("EnvironObj")
A7 = test:convert(A7)
A7:addModel(asteroid_1)
--a7RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 0.0, posX, posY, posZ, 0.0, 0.0, 0.0)
--A7:SetRigidBody(a7RigidBody)
A7:updateObject(posX, posY, posZ)
--print ("Model finished ")