print ("Model loading ")
ModManager = MM.ModelManager();

print ("Model radar ")
ModManager:addModel("assets/Bennu/Bennu Radar.obj")
print ("Model golev ")
ModManager:addModel("assets/golevka/golevka.obj")
print ("Model astro ")
ModManager:addModel("assets/Astronaut/Z2.obj")
print ("Model man ")
ModManager:addModel("assets/man/model.dae")
ModManager:addModel("assets/rocket/spaceship.obj")
ModManager:addModel("assets/Rock/Rock.obj" )

asteroid_1  = ModManager:GetModel("assets/Bennu/Bennu Radar.obj")
asteroid_2 = ModManager:GetModel("assets/golevka/golevka.obj")
astroboy = ModManager:GetModel("assets/Astronaut/Z2.obj")
mon = ModManager:GetModel("assets/man/model.dae")
rocket = ModManager:GetModel("assets/rocket/spaceship.obj")
rock = ModManager:GetModel("assets/Rock/Rock.obj")

print ("Model finished ")