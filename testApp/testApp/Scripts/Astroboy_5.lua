--asteroid object
--print ("First Environmental Object")
a = -3.0
b = -4.0
posX = 213.0
posY = 240 --T1:getHeightAt(4.0,5.0)-22.97
posZ = 210.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_5 = Factory:Create("NPCObj")
Astronaut_5 = test3:convert(Astronaut_5)
Astronaut_5:addModel(mon)
astro5RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_5:SetRigidBody(astro5RigidBody)
Astronaut_5:updateObject(posX, posY, posZ)
--Astronaut_5:updateObjectRotation(270.0,1.0, 0.0, 0.0)
--print ("Model finished ")