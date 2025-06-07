#ifndef PROJECT_VOX_ENGINE_SHADERS_FILE_HPP
#define PROJECT_VOX_ENGINE_SHADERS_FILE_HPP

#include <iostream>
#include <glew.h>
#include <window.hpp>
#include <cmath>

// PROJECT VOX Engine - Static Shader Class
class static_shader{
public:

    //identificador do programa de shader
    unsigned int ID;

    //construtor que vai carregar a fonte do shader, compilar, testar erros e linkar ao programa de shader
    static_shader();

    //ativa o shaader vinculando o programa de shader ao contexto OpenGL
    void activate();

    //vertex shader
    const char* vertex_shader_source = "#version 420 core\n"
        "layout (location = 0) in vec3 aPos; //the position variable has attribute position 0;\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(aPos, 1.0);\n"
        "}";

    //fragment shader
    const char* fragment_shader_source = "#version 420 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 customColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(customColor.xyz, 1.0f);\n"
        "}";

    //testa erros de compilação
    void test_compile_errors();

    //operadores de uniforms

    //insersor de uniform do tipo boolean
    void set_bool_uniform(const std::string &name, bool value) const;  

    //insersor de uniform do tipo int
    void set_int_uniform(const std::string &name, int value) const;

    //insersor de uniform do tipo float
    void set_float_uniform(const std::string &name, float value) const;

    //destrutor
    ~static_shader();
};



#endif //PROJECT_VOX_ENGINE_SHADERS_FILE_HPP