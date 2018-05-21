--asteroid object
--print ("First Environmental Object")
posX = math.random(0.0, 6.0)
posY = 0.0
posZ = math.random(0.0, 9.0)
A3 = Factory:Create("EnvironObj")
A3 = test:convert(A3)
A3:addModel(asteroid_1)
--a3RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 10.0, posX, posY, posZ, 0.0, 0.0, 0.0)
--A3:SetRigidBody(a3RigidBody)
A3:updateObject(posX, posY, posZ)
--print ("Model finished ")