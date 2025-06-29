#ifndef PROJECT_VOX_ENGINE_TEXTURE_SHADER_FILE_HPP
#define PROJECT_VOX_ENGINE_TEXTURE_SHADER_FILE_HPP

#include <iostream>
#include <glew.h>
#include <window.hpp>
#include <cmath>
#include <stb_image.hpp>
#include <glm.hpp>

// PROJECT VOX Engine - Texture Shader Class
class texture_shader{
public:

    //identificador do programa de shader
    unsigned int ID;

    //construtor que vai carregar a fonte do shader, compilar, testar erros e linkar ao programa de shader
    texture_shader();

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

    //operadores de uniforms

    //insersor de uniform do tipo boolean
    void set_bool_uniform(const std::string &name, bool value) const;  

    //insersores de uniform do tipo int
    void set_int_uniform(const std::string &name, int X) const;        //uniform com 1 int
    void set_int_uniform(const std::string &name, int X, int Y) const; //uniform com 2 int

    //insersores de uniform do tipo float
    void set_float_uniform(const std::string &name, float X) const;                            //uniform com 1 float
    void set_float_uniform(const std::string &name, float X, float Y) const;                   //uniform com 2 float
    void set_float_uniform(const std::string &name, float X, float Y, float Z) const;          //uniform com 3 float
    void set_float_uniform(const std::string &name, float X, float Y, float Z, float W) const; //uniform com 4 float

    //destrutor
    ~texture_shader();
};



#endif //PROJECT_VOX_ENGINE_TEXTURE_SHADER_FILE_HPP