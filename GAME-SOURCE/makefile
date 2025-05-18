#Automated compiler for project vox core and game
#PROJECT-VOX branch compiler

#############################
#  COMPILER CONFIG SECTION  #
#############################

#Executable name
TARGET = voxrun

#C++ compiler
CXX = g++

#Compiler flags/args
CXXFLAGS = -Wall



###########################
#  LINKER CONFIG SECTION  #
###########################

#Header directories
INCLUDE_DIRS= -Ilibs/GLEW \
	          -Ilibs/GLFW \
			  -Ilibs/DearImGui \
			  -Isrc/window \
			  -Isrc/vox-engine

              

#Libs directories
LIB_DIRS= -Llibs/GLEW \
		  -Llibs/GLFW \
		  -Llibs/DearImGui


#Included libraries (order matters)
LIBS= -lglew \
      -lGL \
	  -lglfw3 \
	  -limgui
	



##############################
#  DIRECTIVE CONFIG SECTION  #
##############################

#Source files
src = src/main.cpp src/window/window_object.cpp

all:
	@echo $(shell date): Compiling Project-VOX [core] at $(shell hostname) as $(shell whoami)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(src) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)
	@echo Project-VOX [core] compiled! Executable name: $(TARGET)

run:
	@echo $(shell date): Runing Project-VOX [core] at $(shell hostname) via make directive as $(shell whoami)
	@./$(TARGET)
	@echo Test completed!