posX = 350.45
posY = 112 
posZ = 3045.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_1 = Factory:Create("NPCObj")
Astronaut_1 = test3:convert(Astronaut_1)
Astronaut_1:addModel(mon)
astro1RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_1:SetRigidBody(astro1RigidBody)
Astronaut_1:updateObject(posX, posY, posZ)
Astronaut_1:ScaleObject(10);
--Astronaut_1:updateObjectRotation(270.0,1.0, 0.0, 0.0)
--print ("Model finished ")