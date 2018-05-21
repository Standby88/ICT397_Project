--asteroid object
--print ("First Environmental Object")
a = 7.0
b = 14.0
posX = 7.0
posY = 1.5 --T1:getHeightAt(a-50.0, b-50.0)
posZ = 14.0
radius = 0.5
height = 1.8
mass = 60.0
Astronaut_6 = Factory:Create("NPCObj")
Astronaut_6 = test3:convert(Astronaut_6)
Astronaut_6:addModel(astroboy)
astro6RigidBody = PhysicsManager:CreateCapsuleRigidBody(radius, height, mass, posX, posY, posZ)
Astronaut_6:SetRigidBody(astro6RigidBody)
Astronaut_6:updateObject(posX, posY, posZ)
--rotation moves model away from body
--Astronaut_6:updateObjectRotation(180.0,0.0, 1.0, 0.0)
--print ("Model finished ")