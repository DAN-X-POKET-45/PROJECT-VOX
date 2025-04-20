//inclusão do arquivo de definição
#include "window.hpp"

#include <iostream>
#include <string>

//ordem fixa
//#include <glad.h> //Usando o GLAD
#include <glew.h>    //Usando o GLEW
#include <glfw3.h>

window::window(int width, int height, const char* title){
    //verificador de inicializaçao da biblioteca GLFW
    if(!glfwInit()){
        std::cerr << "WINDOW ERROR! GLFW [libglfw3.a] is not initialized" << '\n';
        return;
    }

    //Open GL Version 4.2 NEEDED

    //definição de versão máxima da Open GL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    //definição de versão mínima da Open GL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    //configurador de perfil Open GL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //definição da permissão de redimensionamento da janela
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    //criador do obejto de janela
    glfw_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    //se a criaçao do objeto de janela falhar
    if(!glfw_window){
        glfwTerminate();
        std::cerr << "WINDOW ERROR! Failed to create a GLFW window for some random reason" << '\n';
    }

    //definição da callback de tratamento de erro
    glfwSetErrorCallback(error_callback);

    //tornar o contexto Opengl GL principal na janela GLFW atual
    glfwMakeContextCurrent(glfw_window);

    //PARA O GLAD USADO ANTERIORMENTE
    /*verificador de inicializaçao da biblioteca GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "WINDOW ERROR! Failed to initialize GLAD GL loader for some random reason" << '\n';
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }*/

    //PARA O GLEW

    //verificador de inicializaçao da biblioteca GLEW
    glewExperimental = GL_TRUE; // ativa extensões modernas
    if(glewInit() != GLEW_OK){
        std::cerr << "WINDOW ERROR! Failed to initialize GLEW [libglew.a] for some random reason";
        return;
    }

    //CALLBACKS ESPECIAIS

    //definição da callback de tratamento de dispositivos de entrada
    glfwSetKeyCallback(glfw_window, key_callback);

    //definição da callback de redimensionamento da janela
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

    //habilitar o V-Sync
    glfwSwapInterval(1);

};

//destrutor
window::~window(){
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
}

//verificador de fechamento da janela pelo sistema operacional
bool window::should_close(){
    return glfwWindowShouldClose(glfw_window);
}

//alteração de buffers de renderização
void window::swap_buffers(){
    glfwSwapBuffers(glfw_window);
}

//atualizador de eventos da janela
void window::poll_events(){
    glfwPollEvents();
}

//modificador de tamanho da janela
void window::set_size(int width, int height){
    glfwSetWindowSize(glfw_window, width, height);
}

//modificador de título da janela
void window::set_title(const char* title){
    glfwSetWindowTitle(glfw_window, title);
}

//CALLBACKS

//callback de erro
void window::error_callback(int error, const char* description){
    std::cerr << "GLFW RUNTIME ERROR! [" << error << "]: " << description << '\n';
}

//função de redimensionamento CALLBACK do contexto OpenGL em realação a janela
void window::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    //redimensiona o viewport da janela
    glViewport(0, 0, width, height);

    //depurador de redimencionamento
    std::cout << "WINDOW RESIZED! [" << width << "x" << height << "]" << '\n';
}

//tratamento de condicionais CALLBACK de entrada da janela GLFW
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