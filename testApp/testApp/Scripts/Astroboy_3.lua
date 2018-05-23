posX = 4.0 
posY = 0.0
posZ = 12.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_3 = Factory:Create("NPCObj")
Astronaut_3 = test3:convert(Astronaut_3)
Astronaut_3:addModel(mon)
astro3RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_3:SetRigidBody(astro3RigidBody)
Astronaut_3:updateObject(4.0, 0.0, 12.0)
Astronaut_3:updateObjectRotation(270.0,1.0, 0.0, 0.0)
--print ("Model finished ")