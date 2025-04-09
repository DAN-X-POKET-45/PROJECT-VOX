#static library name
TARGET = libimgui.a

#compiler
CXX = g++

#compiler flags
CXXFLAGS = -Wall -O2

#ar tool for creating static libraries
AR = ar

#ar flags
ARFLAGS = rcs

#source files
SRCS = $(wildcard *.cpp)

#object files (mapped from the source files)
OBJS = $(SRCS:.cpp=.o)

#default target: create the static library
all: $(TARGET)

#rule to create the static library
$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

#rule to compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean up generated files
clean:
	rm -f $(OBJS)

.PHONY: all clean