--asteroid object
--print ("First Environmental Object")
posX = 15.0
posY = 0.0
posZ = 11.0
A4 = Factory:Create("EnvironObj")
A4 = test:convert(A4)
A4:addModel(asteroid_2)
--a4RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 0.0, posX, posY, posZ, 0.0, 0.0, 0.0)
--A4:SetRigidBody(a4RigidBody)
A4:updateObject(posX, posY, posZ)
--print ("Model finished ")