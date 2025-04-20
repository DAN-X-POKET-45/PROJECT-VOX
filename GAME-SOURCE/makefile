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
			  -Isrc/window

              

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


#GLAD lib
#LIBS= -Ilibs/GLAD -Llibs/GLAD -lglad

#Open GL lib
#LIBS+= -lGL

#GLFW lib
#LIBS+= -Ilibs/GLFW -Llibs/GLFW -lglfw3

#DearImGui lib
#LIBS+= -Ilibs/DearImGui -Llibs/DearImGui -limgui

#Custom lib for window creating
#LIBS+= -Isrc/window

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