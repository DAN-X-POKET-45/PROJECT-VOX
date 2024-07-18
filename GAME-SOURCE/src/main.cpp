#include <iostream>
#include "window/window.hpp"

int main(){
    window game_window(600, 400, "VOX TEST");

    while (!game_window.should_close()) {
        //Renderização (limpa a tela com a cor preta)
        glClear(GL_COLOR_BUFFER_BIT);

        //Troca os buffers front e back
        game_window.swap_buffers();

        //Processa eventos de entrada
        game_window.poll_events();

        //janela da aplicação finalizada
    }
    return 0;
}