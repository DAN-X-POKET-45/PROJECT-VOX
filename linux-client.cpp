#include <iostream>
#include <stdlib.h>

void update(){
    system("cd ~/PROJEECT-VOX");
    system("git pull");
}

void repair(){
	
}

void help(){
    std::cout << "===========================CREDITS==========================="   << std::endl;
    std::cout << "                  PROJECT VOX - GAME CLIENT"                     << std::endl;
    std::cout << "                       A game by DAN-X"                          << std::endl;
    std::cout << "===========================CREDITS===========================\n" << std::endl;

    std::cout << "===========================OPTIONS===========================" << std::endl;
    std::cout << "<update>  --> update project vox core files" << std::endl;
    std::cout << "<version> --> show the current version on your cool gaming PC" << std::endl;
    std::cout << "<start>   --> launch the game as a NORMAL USER" << std::endl;
    std::cout << "<usercfg> --> open theaccount config page for VOX accounts" << std::endl;
    std::cout << "<you>     --> show your activated account" << std::endl;
    std::cout << "<wallet>  --> open your local vox wallet page" << std::endl;
    std::cout << "<node>    --> open your local vox FULL NODE DAEMON if exist" << std::endl;
    std::cout << "<remove>  --> erase project vox" << std::endl;
    std::cout << "<server>  --> (server IP, DOMAIN or NAME) view server info" << std::endl;
    std::cout << "<help>    --> show this message" << std::endl;
    std::cout << "<help-me> --> client tutorial to learn how to config this app" << std::endl;
    std::cout << "<exit>    --> clean the terminal and close the client" << std::endl;
    std::cout << "===========================OPTIONS===========================\n" << std::endl;
}



int main(int argc, char **argv){
    MENU:
    help();
}
