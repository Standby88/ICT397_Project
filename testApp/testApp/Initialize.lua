-- Initialization script

print "Initialize called"
-- create factory to create objects on gameobjects
Factory = GAF.GameAssetFactory()

-- declare creators
EOC = GAC.EOCreator()
PC = GAC.PCreator()

-- register create functions into factory
Factory:Register("E", EOC)
Factory:Register("P", PC)

-- Create objects:
-- 3 environment objects
-- 1 player object 
E1 = Factory:Create("E")
E2 = Factory:Create("E")
E3 = Factory:Create("E")
P1 = Factory:Create("P")

-- assign environment obj into the environment obj manager
EnObjMan = EOM.EnvironmentObjManager()
EnObjMan:addObject(E1, "Item1")
EnObjMan:addObject(E2, "Item2")
EnObjMan:addObject(E3, "Item3")

-- assign player to character manager
ChMan = CM.CharacterManager()
ChMan:addPlayer(P1)
