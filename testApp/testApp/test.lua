local fac = F.Factory()

local Cr = C.DerivedCreatorA()
local Cv = C.DerivedCreatorB()
local V = B.DerivedA()

fac:Register("Db", Cv)
fac:Register("Da", Cr)
b = fac:Create("Da")
a = fac:Create("Db")
