#Extensive Definition Language - XDL
#PROJECT-VOX branch compiler

echo COMPILING XDL 12
g++ -o xdl_program_test example.cpp XDL_parser_12.0_BETA.cpp
echo XDL lib compiled!
echo run!
./xdl_program_test
echo test completed!