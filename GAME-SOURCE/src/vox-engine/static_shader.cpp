#include <iostream>
#include <glew.h>
#include <window.hpp>
#include <cmath>
#include <shaders.hpp>

static_shader::static_shader(){
    //define os shaders de vértice e fragmento
    unsigned int vertex_shader, fragment_shader;

    //buffers de armazenamento de informações e teste de erro
    int success;
    char error_log[512];

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
void static_shader::activate(){
    //ativa o shader vinculando o programa de shader ao contexto OpenGL
    glUseProgram(ID);
}

//destrutor
static_shader::~static_shader(){
    //destrutor do programa de shader
    glDeleteProgram(ID);
}

//insersor de uniform do tipo boolean
void static_shader::set_bool_uniform(const std::string &name, bool value)const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

//insersor de uniform do tipo int
void static_shader::set_int_uniform(const std::string &name, int value)const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

//insersor de uniform do tipo float
void static_shader::set_float_uniform(const std::string &name, float value)const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 
