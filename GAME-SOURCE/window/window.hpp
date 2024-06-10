#ifndef WINDOW_HPP
#define WINDOW_HPP

//inclusão das bibliotecas necessárias
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

class window{
public:
    //[CONSTRUTOR] Define a pré-configuração da jenela
    window(int width, int height, const char* title);

    //verificador de fechamento de janela
    bool should_close();

    //troca de buffers
    void swap_buffers();

    //atualizador de eventos
    void poll_events();

    //define o tamanho da janela
    void set_size(int width, int height);

    //define o título da janela
    void set_tittle(const char* tittle);

    //destrutor de obejtos de janela
    ~window();

private:
    GLFWwindow* glfw_window;

    //função de erro CALL-BACK obrigatória da biblioteca GLFW
    static void error_callback(int error, const char* description);
};


#endif //WINDOW_HPP