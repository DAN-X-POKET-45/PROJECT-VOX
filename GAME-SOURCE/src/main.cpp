#include <iostream>
#include <glad.h>
#include <GL/gl.h>
#include <window.hpp>
//#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>

int main(){
    window game_window(600, 400, "VOX TEST"); //Objeto de janela personalizado

    

    //enquanto a janela não receber um sinal de fechamento
    while(!game_window.should_close()){
        //Processa eventos de entrada
        game_window.poll_events();

        //processa o tamanho da janela e redimenciona o contexto Open GL
        int main_game_window_w, main_game_window_h;
        glfwGetFramebufferSize(game_window.glfw_window, &main_game_window_w, &main_game_window_h);
        glViewport(0, 0, main_game_window_w, main_game_window_h);

        //Limpar a tela com uma cor de fundo
        glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Projeto de triângulo
        float triangleVertices[] = {
            0.0f,  0.5f,  //Topo
           -0.5f, -0.5f,  //Esquerda
            0.5f, -0.5f   //Direita
        };


        //Troca os buffers front e back
        game_window.swap_buffers();

        //Janela da aplicação finalizada
    }

    return 0;
}