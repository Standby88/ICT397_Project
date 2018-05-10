--asteroid object
--print ("First Environmental Object")
posX = 0.0
posY = 0.0
posZ = 0.0
A1 = Factory:Create("EnvironObj")
A1 = test:convert(A1)
A1:addModel(asteroid_1)
a1RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 0.0, posX, posY, posZ, 0.0, 0.0, 0.0)
A1:SetRigidBody(a1RigidBody)
A1:updateObject(posX, posY, posZ)
--print ("Model finished ")
--print(T1:getHeightAt(0.0,0.0))