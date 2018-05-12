posX = 4.0
posY = T1:getHeightAt(4.0,5.0)-22.97
posZ = 5.0
Astronaut_1 = Factory:Create("NPCObj")
Astronaut_1 = test3:convert(Astronaut_1)
Astronaut_1:addModel(astroboy)
--astro1RigidBody = PhysicsManager:CreateBoxRigidBody(1.80, 1.0, 0.5, 0.0, posX, posY, posZ)
--Astronaut_1:SetRigidBody(astro1RigidBody)
Astronaut_1:updateObject(posX, posY, posZ)
--print ("Model finished ")