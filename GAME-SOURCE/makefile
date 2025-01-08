#Automated compiler for project vox core and game
#PROJECT-VOX branch compiler

#Executable name
TARGET = voxrun

#compier
CXX = g++

#Compiler flags
CXXFLAGS = -Wall

#Compiler additional libs
LIBS = -lGL

#GLFW custom lib
LIBS+= -Isrc/libs/GLFW -Lsrc/libs/GLFW -lglfw3

#DearImGui custom lib
LIBS+= -Isrc/libs/DearImGui -Lsrc/libs/DearImGui -limgui

#Source files
src = src/main.cpp src/window/window_object.cpp

#DearImGui
src += $(wildcard src/libs/DearImGui/*.cpp)

all:
	@echo $(shell date): Compiling Project-VOX [core] at $(shell hostname)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(src) $(LIBS)
	@echo Project-VOX [core] compiled!


run:
	@echo $(shell date): Runing Project-VOX [core] at $(shell hostname) via make directive
	@./$(TARGET)
	@echo Test completed!