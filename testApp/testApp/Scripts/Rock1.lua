--R1
R1posX = 2100.0
R1posY = 180.0
R1posZ = 4300.0
Ro1 = Factory:Create("EnvironObj")
Ro1 = test:convert(Ro1)
Ro1:addModel(rock)
Ro1Rigid = PhysicsManager:CreateBoxRigidBody(100, 100.0, 100, 0,  R1posX, R1posY, R1posZ)
Ro1:SetRigidBody(Ro1Rigid)
Ro1:updateObject(R1posX, R1posY, R1posZ)
Ro1:ScaleObject(210)
Ro1:updateObjectRotation(25.0,0.0, 0.0, 1.0)
Ro1:setStatic(true)

--R2
R2posX = 2500.0
R2posY = 80.0
R2posZ = 3100.0
Ro2 = Factory:Create("EnvironObj")
Ro2 = test:convert(Ro2)
Ro2:addModel(rock)
Ro2Rigid = PhysicsManager:CreateBoxRigidBody(80, 80, 80, 0,  R2posX, R2posY, R2posZ)
Ro2:SetRigidBody(Ro2Rigid)
Ro2:updateObject(R2posX, R2posY, R2posZ)
Ro2:ScaleObject(160)
Ro2:updateObjectRotation(25.0,0.0, 0.0, 1.0)
Ro2:setStatic(true)

--R3
R3posX = 3600.0
R3posY = 100.0
R3posZ = 1200.0
Ro3 = Factory:Create("EnvironObj")
Ro3 = test:convert(Ro3)
Ro3:addModel(rock)
Ro3Rigid = PhysicsManager:CreateBoxRigidBody(55, 55, 55, 0,  R3posX, R3posY, R3posZ)
Ro3:SetRigidBody(Ro3Rigid)
Ro3:updateObject(R3posX, R3posY, R3posZ)
Ro3:ScaleObject(110)
Ro3:updateObjectRotation(25.0,0.0, 0.0, 1.0)
Ro3:setStatic(true)

--R4
R4posX = 4800.0
R4posY = 100.0
R4posZ = 2750.0
Ro4 = Factory:Create("EnvironObj")
Ro4 = test:convert(Ro4)
Ro4:addModel(rock)
Ro4Rigid = PhysicsManager:CreateBoxRigidBody(140, 140, 140, 0,  R4posX, R4posY, R4posZ)
Ro4:SetRigidBody(Ro4Rigid)
Ro4:updateObject(R4posX, R4posY, R4posZ)
Ro4:ScaleObject(280)
Ro4:updateObjectRotation(25.0,0.0, 0.0, 1.0)
Ro4:setStatic(true)

--R5
R5posX = 910.0
R5posY = 100.0
R5posZ = 845.0
Ro5 = Factory:Create("EnvironObj")
Ro5 = test:convert(Ro5)
Ro5:addModel(rock)
Ro5Rigid = PhysicsManager:CreateBoxRigidBody(90, 90, 90, 0, R5posX, R5posY, R5posZ)
Ro5:SetRigidBody(Ro5Rigid)
Ro5:updateObject(R5posX, R5posY, R5posZ)
Ro5:ScaleObject(180)
Ro5:updateObjectRotation(25.0,0.0, 0.0, 1.0)
Ro5:setStatic(true)
