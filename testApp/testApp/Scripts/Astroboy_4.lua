--asteroid object
--print ("First Environmental Object")
a = 12.0	--a and b were substituted in for an x and y that were used to calculate posY
b = -5.0
posX = 211.0
posY = 240 --T1:getHeightAt(4.0,5.0)-22.97
posZ = 209.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_4 = Factory:Create("NPCObj")
Astronaut_4 = test3:convert(Astronaut_4)
Astronaut_4:addModel(mon)
astro4RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_4:SetRigidBody(astro4RigidBody)
Astronaut_4:updateObject(posX, posY, posZ)
--Astronaut_4:updateObjectRotation(270.0,1.0, 0.0, 0.0)
--print ("Model finished ")