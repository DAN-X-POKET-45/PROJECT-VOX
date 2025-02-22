#ifndef WINDOW_OBJECT_HPP
#define WINDOW_OBJECT_HPP

#include <iostream>
#include <string>
#include "../libs/GLFW/glfw3.h"

class window{
public:
    /*===================================*/
    /*       Declarações do GLFW3        */
    /*===================================*/
    
    //[CONSTRUTOR] Define a pré-configuração da jenela
    window(int width=300, int height=200, const char* title="unamed window");

    //objeto da janela glfw
    GLFWwindow* glfw_window;

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

    //destrutor de obejto da janela
    ~window();

private:
    //função de erro CALL-BACK obrigatória da biblioteca GLFW
    static void error_callback(int error, const char* description);

    //função de detecção de pressionamento de teclas
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


#endif //WINDOW_OBJECT_HPP