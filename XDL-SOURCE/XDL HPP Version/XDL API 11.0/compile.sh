#Extensive Definition Language - XDL
#PROJECT-VOX branch compiler

echo COMPILING XDL 11
g++ -o xdl_program_test example.cpp XDL_parser_11.0_BETA.cpp
echo XDL lib compiled!
echo run!
./xdl_program_test
echo test completed!