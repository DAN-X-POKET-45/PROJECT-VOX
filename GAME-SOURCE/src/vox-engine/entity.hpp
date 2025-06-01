#include <iostream>
#include <glew.h>
#include <window.hpp>

class test_entity{
    test_entity();
    ~test_entity();

    void compile_shader();
    void draw();
    void set_position(float x, float y, float z);
    void set_scale(float x, float y, float z);
}