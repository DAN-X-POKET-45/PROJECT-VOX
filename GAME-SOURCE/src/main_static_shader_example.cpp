#include <iostream>
#include <glew.h>
#include <window.hpp>
#include <cmath>
#include <static_shader.hpp>



int main(){
    window game_window(600, 400, "VOX TEST"); //Objeto de janela personalizado

    static_shader shader; //objeto de shader estático
    shader.activate(); //ativa o shader

    //Projeto de triângulo duplo 2D
    float triangleVertices[] = {
        //positions
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
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

    //CONFIGURAÇÃO DE PONTEIROS DE ATRIBUTOS DE VÉRTICE

    //atributo de posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

        //define a cor do polígono
        shader.set_float_uniform("customColor", 0.5f, 1.0f, 0.5f, 1.0f);

        //glDrawArrays(GL_TRIANGLES, 0, 3); //Desenha o triângulo a partir de um arraay de vértices VBO
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //Desenha o triângulo duplo a partir de elementos no EBO

        //Troca os buffers front e back
        game_window.swap_buffers();

        //Janela da aplicação finalizada
    }

    return 0;
}