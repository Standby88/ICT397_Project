--asteroid object
--print ("First Environmental Object")
posX = 20.0
posY = 200.0
posZ = 20.0
A1 = Factory:Create("EnvironObj")
A1 = test:convert(A1)
A1:addModel(asteroid_1)
a1RigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 10.0, posX, posY, posZ, 0.0, 0.0, 0.0)
A1:SetRigidBody(a1RigidBody)
A1:updateObject(posX, posY, posZ)
A1:SetIdlePos(posX, posY, posZ)

moveposX = 0
moveposY = 200
moveposZ = 0
A1:SetMovePos(moveposX, moveposY, moveposZ)
--print ("Model finished ")
--print(T1:getHeightAt(0.0,0.0))