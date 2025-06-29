#include <iostream>
#include <glew.h>
#include <window.hpp>
#include <cmath>
#include <glm.hpp>
#include <stb_image.hpp>
#include <texture_shader.hpp>


texture_shader::texture_shader(){
    //define os shaders de vértice e fragmento
    unsigned int vertex_shader, fragment_shader;

    //buffers de armazenamento de informações e teste de erro
    int success;
    char error_log[1024];

    //compilação do vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    //testa erros de compilação do vertex shader
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, error_log);
        std::cout << "VOX-ENGINE COMPILE ERROR!!! [SHADER: static_shader::vertex_shader] : " << error_log << '\n';
    };

    //compilação do fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    //testa erros de compilação do fragment shader
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, error_log);
        std::cout << "VOX-ENGINE COMPILE ERROR!!! [SHADER: static_shader::fragment::shader] : " << error_log << '\n';
    };

    //criação do programa de shader
    ID = glCreateProgram();

    //Anexação de shaders ao programa
    glAttachShader(ID, vertex_shader);    //anexa o vertex shader ao programa
    glAttachShader(ID, fragment_shader);  //anexa o fragment shader ao programa
    
    //linka o programa de shader
    glLinkProgram(ID);
    
    //testa erros de linkagem do programa de shader
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, error_log);
        std::cout << "VOX-ENGINE SHADER PROGRAM LINK ERROR!!! [SHADER: static_shader::ID] : " << error_log << '\n';
    }

    //limpeza de shaders já linkados
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

//usa o shader
void texture_shader::activate(){
    //ativa o shader vinculando o programa de shader ao contexto OpenGL
    glUseProgram(ID);
}

//destrutor
texture_shader::~texture_shader(){
    //destrutor do programa de shader
    glDeleteProgram(ID);
}

//insersor de uniform do tipo boolean
void texture_shader::set_bool_uniform(const std::string &name, bool value)const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}



//insersores de uniform do tipo int
void texture_shader::set_int_uniform(const std::string &name, int X)const{ //uniform com 1 int
    glUniform1i(glGetUniformLocation(ID, name.c_str()), X);
}

void texture_shader::set_int_uniform(const std::string &name, int X, int Y)const{ //uniform com 2 int
    glUniform2i(glGetUniformLocation(ID, name.c_str()), X, Y);
}



//insersores de uniform do tipo float
void texture_shader::set_float_uniform(const std::string &name, float X)const{ //uniform com 1 float
    glUniform1f(glGetUniformLocation(ID, name.c_str()), X); 
}

void texture_shader::set_float_uniform(const std::string &name, float X, float Y)const{ //uniform com 2 float
    glUniform2f(glGetUniformLocation(ID, name.c_str()), X, Y);
}

void texture_shader::set_float_uniform(const std::string &name, float X, float Y, float Z)const{ //uniform com 3 float
    glUniform3f(glGetUniformLocation(ID, name.c_str()), X, Y, Z);
}

void texture_shader::set_float_uniform(const std::string &name, float X, float Y, float Z, float W)const{ //uniform com 4 float
    glUniform4f(glGetUniformLocation(ID, name.c_str()), X, Y, Z, W);
}
