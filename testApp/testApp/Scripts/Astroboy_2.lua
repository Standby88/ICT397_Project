posX = 8.0 
posY = T1:getHeightAt(8.0, 5.0)-22.97
posZ = 5.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_2 = Factory:Create("NPCObj")
Astronaut_2 = test3:convert(Astronaut_2)
Astronaut_2:addModel(astroboy)
astro2RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_2:SetRigidBody(astro2RigidBody)
Astronaut_2:updateObject(posX, posY, posZ)
-- rotation moves model away from body
--Astronaut_2:updateObjectRotation(88.0,0.0, 1.0, 0.0)
--print ("Model finished ")