#Main game code - Project VOX
#PROJECT-VOX branch compiler

echo COMPILING PROJECT-VOX 0.0
g++ -o voxrun main.cpp window/window_object.cpp -lglfw  -lGL
echo PROJECT-VOX compiled!