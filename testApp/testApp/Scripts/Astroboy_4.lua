--asteroid object
--print ("First Environmental Object")
posX = 4560.0
posY = 34.32
posZ = 4538
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_4 = Factory:Create("NPCObj")
Astronaut_4 = test3:convert(Astronaut_4)
Astronaut_4:addModel(mon)
astro4RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_4:SetRigidBody(astro4RigidBody)
Astronaut_4:updateObject(posX, posY, posZ)
Astronaut_4:ScaleObject(10)
--Astronaut_4:updateObjectRotation(270.0,1.0, 0.0, 0.0)
--print ("Model finished ")