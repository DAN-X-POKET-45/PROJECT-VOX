#Automated compiler for Extensive Definition Language - XDL
#PROJECT-VOX branch compiler

#############################
#  COMPILER CONFIG SECTION  #
#############################

#Executable name
TARGET = xdl_program_test

#C++ compiler
CXX = g++

#Compiler flags/args
CXXFLAGS = -Wall

#static library archiver
AR = ar

#static library archiver args
ARFLAGS = rcs



###########################
#  LINKER CONFIG SECTION  #
###########################

#Header directories
INCLUDE_DIRS= -Iinclude

              

#Libs directories
#LIB_DIRS= -Llibs/GLEW \




#Included libraries (order matters)
#LIBS= -lglew \
	


##############################
#  DIRECTIVE CONFIG SECTION  #
##############################

#Source files
src = src/main.cpp \
	  src/xdl_dynamic_object_iplementation.cpp \
	  src/xdl_parser_implementation.cpp \
	  src/xdl_file_writer_implementation.cpp \
	  src/xdl_validator_implementation.cpp \
	  src/xdl_logging.cpp

all:
	@echo $(shell date): Compiling Extensive Direct Language [XDL] library at $(shell hostname) as $(shell whoami)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(src) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)
	@echo Extensive Direct Language library [XDL] lib compiled! Executable name: $(TARGET)

run:
	@echo $(shell date): Runing Extensive Direct Language [XDL] library at $(shell hostname) via make directive as $(shell whoami)
	@./$(TARGET)
	@echo Executable run completed!