posX = 0
posY = 0
posZ = 0
Monster = Factory:Create("NPCObj")
Monster = test3:convert(Monster)
Monster:addModel(mon)
Monster:updateObject(posX, posY, posZ)
Monster:updateObjectRotation(270.0,1.0, 0.0, 0.0)