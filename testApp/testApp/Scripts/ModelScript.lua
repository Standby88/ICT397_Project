print ("Model loading ")
ModManager = MM.ModelManager();

print ("Model radar ")
ModManager:addModel("assets/Bennu/Bennu Radar.obj")
print ("Model golev ")
ModManager:addModel("assets/golevka/golevka.obj")
print ("Model astro ")
ModManager:addModel("assets/Astronaut/Z2.obj")
print ("Model man ")
ModManager:addModel("assets/man/model.fbx")
ModManager:addModel("assets/Rock2/RockCluster1.dae")
asteroid_1  = ModManager:GetModel("assets/Bennu/Bennu Radar.obj")
asteroid_2 = ModManager:GetModel("assets/golevka/golevka.obj")
astroboy = ModManager:GetModel("assets/Astronaut/Z2.obj")
mon = ModManager:GetModel("assets/man/model.dae")
rock1 = ModManager:GetModel("assets/man/model.fbx")
print ("Model finished ")