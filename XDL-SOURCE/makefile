#Extensive Definition Language - XDL
#PROJECT-VOX branch compiler

#compier
CXX = g++

all:
	@echo $(shell date): Compiling Extensive Direct Language [XDL] library at $(shell hostname)
	@g++ -o xdl_program_test main.cpp xdl_dynamic_object_iplementation.cpp xdl_parser_implementation.cpp xdl_file_writer_implementation.cpp xdl_validator_implementation.cpp
	@echo Extensive Direct Language library [XDL] lib compiled!
run:
	@echo $(shell date): Runing Extensive Direct Language [XDL] library at $(shell hostname)
	@./xdl_program_test
	@echo Test completed!

clean:
	@echo $(shell date): Cleaning Extensive Direct Language library compiled...
	@rm xdl_program_test
	@echo $(shell date): Cleaned

install:
