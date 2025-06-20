#ifndef WINDOW_OBJECT_HPP
#define WINDOW_OBJECT_HPP

#include <iostream>
#include <string>

//ordem fixa
//#include <glad.h> //Usando o GLAD
#include <glew.h> //Usando o GLEW
#include <glfw3.h>

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
    void set_title(const char* title);

    //alternador de função de entrada de usuário
    void swap_key_callback(void(*callback)(int, int, int, int));

    //destrutor de obejto da janela
    ~window();

private:
    //função de erro CALLBACK obrigatória da biblioteca GLFW
    static void error_callback(int error, const char* description);

    //função de redimensionamento CALLBACK do contexto OpenGL em realação a janela
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    //ESPAÇO DE FUNÇÕES PARA A DINAMICA DE ALTERNADOR DE KEY CALLBACK
    //função simples sem a nserção na assinatura dde função da glfw_windowd
    static void (*custom_callback)(int, int, int, int); // ponteiro para a função simples
    //função CALLBACK de detecção de entrada de usuário
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    //wrapper para passar ao GLFW
    static void key_callback_wrapper(GLFWwindow* window, int key, int scancode, int action, int mods);

};


#endif //WINDOW_OBJECT_HPP