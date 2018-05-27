posX = 2161.26
posY = 90.51
posZ = 2189.59
R = Factory:Create("EnvironObj")
R = test:convert(R)
R:addModel(rocket)
RRigidBody = PhysicsManager:CreateBoxRigidBody(80, 150.0, 30.0, 0.0,posX-30, posY, posZ+50)
R:SetRigidBody(RRigidBody)
R:setStatic(true)
R:ScaleObject(100)
R:updateObject(posX, posY, posZ)
R:updateObjectRotation(25.0,0.0, 0.0, 1.0)