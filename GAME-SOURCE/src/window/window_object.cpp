//inclusão do arquivo de definição
#include "window.hpp"

//inclusão das bibliotecas necessárias
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

window::window(int width, int height, const char* title){
    //verificador de inicializaçao da biblioteca GLFW
    if(!glfwInit()){
        std::cerr << "WINDOW ERROR! GLFW is not initialized" << '\n';
    }

    //definição de versão máxima
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    //definição de versão mínima
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //configurador de perfil Open GL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //definição da permissão de redimensionamento da janela
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    //criador do obejto de janela
    glfw_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    //definição da callback de tratamento de erro
    glfwSetErrorCallback(error_callback);

    //definição da callback de tratamento de dispositivos de entrada
    glfwSetKeyCallback(glfw_window, key_callback);

    //se a criaçao do objeto de janela falhar
    if (!glfw_window){
        glfwTerminate();
        std::cerr << "WINDOW ERROR! Failed to create a GLFW window" << '\n';
    }

};

//destrutor
window::~window(){
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
}

//verificador de janela
bool window::should_close(){
    return glfwWindowShouldClose(glfw_window);
}

//troca de buffers
void window::swap_buffers(){
    glfwSwapBuffers(glfw_window);
}

//atualizador de eventos
void window::poll_events(){
    glfwPollEvents();
}

//definidor do tamanho da janela
void window::set_size(int width, int height){
    glfwSetWindowSize(glfw_window, width, height);
}

// Define o título da janela
void window::set_tittle(const char* title){
    glfwSetWindowTitle(glfw_window, title);
}

//tratamento de erros

//callback de erro
void window::error_callback(int error, const char* description){
    std::cerr << "Error: (" << error << "): " << description << std::endl;
}

//tratamento de condicionais de entrada
void window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch(key){
            case GLFW_KEY_W:
                std::cout << "W key is pressed" << std::endl;
                break;
            case GLFW_KEY_S:
                std::cout << "S key is pressed" << std::endl;
                break;
            case GLFW_KEY_A:
                std::cout << "A key is pressed" << std::endl;
                break;
            case GLFW_KEY_D:
                std::cout << "D key is pressed" << std::endl;
                break;
            default:
                break;
        }
    }
}