#Automated compiler for project vox core and game
#PROJECT-VOX branch compiler

#Executable name
TARGET = voxrun

#C++ compier
CXX = g++

#Compiler flags/args
CXXFLAGS = -Wall

#Compiler additional libs
LIBS = -lGL

#GLFW custom lib
LIBS+= -Isrc/libs/GLFW -Lsrc/libs/GLFW -lglfw3

#DearImGui custom lib
LIBS+= -Isrc/libs/DearImGui -Lsrc/libs/DearImGui -limgui

#Custom lib for window creating
LIBS+= -Isrc/window

#Source files
src = src/main.cpp src/window/window_object.cpp

#DearImGui
src += $(wildcard src/libs/DearImGui/*.cpp)

all:
	@echo $(shell date): Compiling Project-VOX [core] at $(shell hostname) as $(shell whoami)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(src) $(LIBS)
	@echo Project-VOX [core] compiled! Executable name: $(TARGET)

run:
	@echo $(shell date): Runing Project-VOX [core] at $(shell hostname) via make directive as $(shell whoami)
	@./$(TARGET)
	@echo Test completed!