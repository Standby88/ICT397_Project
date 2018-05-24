--asteroid object
--print ("First Environmental Object")
a = 7.0
b = 14.0
posX = 205.0
posY = 240 --T1:getHeightAt(4.0,5.0)-22.97
posZ = 207.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_6 = Factory:Create("NPCObj")
Astronaut_6 = test3:convert(Astronaut_6)
Astronaut_6:addModel(mon)
astro6RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_6:SetRigidBody(astro6RigidBody)
Astronaut_6:updateObject(posX, posY, posZ)
--Astronaut_6:updateObjectRotation(270.0,1.0, 0.0, 0.0)
--print ("Model finished ")