posX = 825.66
posY = 56.13 
posZ = 745.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_2 = Factory:Create("NPCObj")
Astronaut_2 = test3:convert(Astronaut_2)
Astronaut_2:addModel(mon)
astro2RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_2:SetRigidBody(astro2RigidBody)
Astronaut_2:updateObject(posX, posY, posZ)
Astronaut_2:ScaleObject(10);
--Astronaut_2:updateObjectRotation(270.0,1.0, 0.0, 0.0)
--print ("Model finished ")