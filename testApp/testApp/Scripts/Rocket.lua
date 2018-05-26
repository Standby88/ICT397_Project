posX = 2161.26
posY = 20.51
posZ = 2189.59
R = Factory:Create("EnvironObj")
R = test:convert(R)
R:addModel(rocket)
RRigidBody = PhysicsManager:CreateSphereRigidBody(0.10, 10.0, posX, posY, posZ, 0.0, 0.0, 0.0)
R:SetRigidBody(RRigidBody)
R:updateObject(posX, posY, posZ)