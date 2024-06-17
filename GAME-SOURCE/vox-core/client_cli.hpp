#ifndef TERMINAL_GRAPHICS_HPP
#define TERMINAL_GRAPHICS_HPP

#include <iostream>
#include <string>

namespace voxcli{

//  sistema de ajuda
    void help(){
        std::cout << "===========================CREDITS==========================="   << '\n';
        std::cout << "                  PROJECT VOX - GAME CLIENT"                     << '\n';
        std::cout << "                       A game by DAN-X"                          << '\n';
        std::cout << "===========================CREDITS===========================\n" << '\n';

        std::cout << "===========================OPTIONS===========================" << '\n';
        std::cout << "<play>    --> launch the game as a NORMAL USER" << '\n';
        std::cout << "<usercfg> --> open theaccount config page for VOX accounts" << '\n';
        std::cout << "<whoami>  --> show your activated account" << '\n';
        std::cout << "<wallet>  --> open your local vox wallet page" << '\n';
        std::cout << "<node>    --> open your local vox FULL NODE DAEMON if exist" << '\n';
        std::cout << "<remove>  --> erase project vox" << '\n';
        std::cout << "<server>  --> (server IP, DOMAIN or NAME) view server info" << '\n';
        std::cout << "<help>    --> show this message" << '\n';
        std::cout << "<help-me> --> client tutorial to learn how to config this app" << '\n';
        std::cout << "<exit>    --> clean the terminal and close the client" << '\n';
        std::cout << "===========================OPTIONS===========================\n" << '\n';
    }


//  sistema de ontrole de usuários
    void authentication(){ //autenticador, uso restrito

    }
    
    void profile_creator(){ //criador de perfil de usuário

    }

    void profile_viewer(std::string user_id){ //motor de busca de perfis de usuários

    }

    void whoami(){ //mostra o perfil ativo no momento

    }

    void user_config(){ //mostra arquivo e configuração

    }

//  controle de entrada e saída

    void exit_process(){
        
    }

//  tratamento de erro

    void error(int number, std::string error_name){
        
    }

} //namespace end

#endif //TERMINAL_GRAPHICS_HPP