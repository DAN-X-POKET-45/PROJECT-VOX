#include <iostream>
#include <GL/gl.h>
#include "window/window.hpp"
#include "libs/DearImGui/imgui.h"
#include "libs/DearImGui/imgui_impl_glfw.h"
#include "libs/DearImGui/imgui_impl_opengl3.h"

int main(){
    window game_window(600, 400, "VOX TEST");

    // Configurar o Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark(); // Estilo padrão

    // Configurar os backends
    ImGui_ImplGlfw_InitForOpenGL(game_window.glfw_window, true);
    ImGui_ImplOpenGL3_Init("#version 420");

    
    while(!game_window.should_close()){
        //Processa eventos de entrada
        game_window.poll_events();

        // Iniciar frame do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Mostrar a Demo Window
        bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(game_window.glfw_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        // Limpar a tela com uma cor de fundo
        glClearColor(1.0f, 0.5f, 0.5f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Troca os buffers front e back
        game_window.swap_buffers();

        //janela da aplicação finalizada
    }

    // Limpeza
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}