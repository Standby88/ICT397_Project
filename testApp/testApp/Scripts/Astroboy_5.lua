--asteroid object
--print ("First Environmental Object")
a = -3.0
b = -4.0
posX = -3.0 
posY = T1:getHeightAt(a-50.0, b-50.0)
posZ = -4.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_5 = Factory:Create("NPCObj")
Astronaut_5 = test3:convert(Astronaut_5)
Astronaut_5:addModel(astroboy)
astro5RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_5:SetRigidBody(astro5RigidBody)
Astronaut_5:updateObject(posX, posY, posZ)
-- rotation moves model away from body
--Astronaut_5:updateObjectRotation(120.0,0.0, 1.0, 0.0)
--print ("Model finished ")