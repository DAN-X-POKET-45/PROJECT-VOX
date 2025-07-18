#include <iostream>
#include <glew.h>
#include <window.hpp>
#include <cmath>
//#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>

unsigned int shaderProgram; //variável global para o programa de shader

//pré configuração para shader

void standardShader(){
    const char* vertexShaderSource = "#version 420 core\n"
        "layout (location = 0) in vec3 aPos; //the position variable has attribute position 0;\n"
        "layout (location = 1) in vec3 aColor; //the color variable has attribute position 1)\n"
        "out vec3 customColor; //output a color to the fragment shader\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(aPos, 1.0);\n"
            "customColor = aColor;\n"
        "}";

    const char* fragmentShaderSource = "#version 420 core\n"
        "out vec4 FragColor;\n"
        "in vec3 customColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(customColor, 1.0);\n"
        "}";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //código constante de verificação de sucesso de compilação do vertexShader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: VERTEX SHADER COMPILATION_FAILED" << "\n" << infoLog << "\n";
    };

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //fim da compilação de shaders

    //início da criação do programa de shader

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);    //anexa o vertex shader ao programa
    glAttachShader(shaderProgram, fragmentShader);  //anexa o fragment shader ao programa
    glLinkProgram(shaderProgram);

    //código constante de verificação de sucesso de construção programa do shaderProgram
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    shaderProgram = shaderProgram; //armazena o programa de shader na variável global

    glUseProgram(shaderProgram); //após esta chamada de função, qualquer desenho de objeto usará este programa de shader
    //logo após o uso do shader, ele pode ser deletado por já ter sido compilado para a GPU
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int main(){
    window game_window(600, 400, "VOX TEST"); //Objeto de janela personalizado

    //Projeto de triângulo duplo 2D
    float triangleVertices[] = {
        //positions        //colors
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
       -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f  // top left 
    };

    //Índices de triângulo duplo 2D
    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    //iniialização de buffers do processo de renderização para testes (VAO)
    unsigned int VAO; //Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //inicialização de buffers do processo de renderização para testes (VBO)
    unsigned int VBO; //Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    //inicialização de buffers do processo de renderização para testes (EBO)
    unsigned int EBO; //Element Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //chamada de compilação, vinculação e uso de shader
    standardShader();

    //CONFIGURAÇÃO DE PONTEIROS DE ATRIBUTOS DE VÉRTICE

    //atributo de posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //atributo de cor de vértice
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    //Veriificação de valor máximo de atributos de vértices suportados pela GPU
    int gpu_max_vertex_attribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &gpu_max_vertex_attribs);
    std::cout << "Max vertex attributes supported by GPU: " << gpu_max_vertex_attribs << '\n';

    //enquanto a janela não receber um sinal de fechamento
    while(!game_window.should_close()){
        //Processa eventos de entrada
        game_window.poll_events();

        //Limpar a tela com uma cor de fundo
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Desenha o triângulo em linhas

        //glDrawArrays(GL_TRIANGLES, 0, 3); //Desenha o triângulo a partir de um arraay de vértices VBO
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //Desenha o triângulo duplo a partir de elementos no EBO

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "customColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        //Troca os buffers front e back
        game_window.swap_buffers();

        //Janela da aplicação finalizada
    }

    return 0;
}