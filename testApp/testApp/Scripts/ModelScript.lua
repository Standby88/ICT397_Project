print ("Model loading ")
ModManager = MM.ModelManager();

ModManager:addModel("assets/Bennu/Bennu Radar.obj")
ModManager:addModel("assets/golevka/golevka.obj")
ModManager:addModel("assets/Astronaut/Z2.obj")
ModManager:addModel("assets/man/model.dae")

asteroid_1  = ModManager:GetModel("assets/Bennu/Bennu Radar.obj")
asteroid_2 = ModManager:GetModel("assets/golevka/golevka.obj")
astroboy = ModManager:GetModel("assets/Astronaut/Z2.obj")
mon = ModManager:GetModel("assets/man/model.dae")
print ("Model finished ")