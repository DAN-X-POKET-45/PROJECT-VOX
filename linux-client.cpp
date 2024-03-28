#include <iostream>
#include <stdlib.h>

void update(){
    system("cd ~/PROJEECT-VOX");
    system("git pull");
}

void repair(){
	
}

void start(){
    std::cout << "=====CREDITS=====" << std::endl;
    std::cout << "PROJECT VOX" << std::endl;
    std::cout << "A game by DAN-X" << std::endl;
    std::cout << "=====CREDITS=====\n" << std::endl;

    std::cout << "===========================OPTIONS===========================" << std::endl;
    std::cout << "<update>  --> update project vox core files" << std::endl;
    std::cout << "<version> --> show the current version on your cool gaming PC" << std::endl;
    std::cout << "<launch>  --> launch the game as a NORMAL USER" << std::endl;
    std::cout << "<usercfg> --> open theaccount config page for VOX accounts" << std::endl;
    std::cout << "<you>     --> show your activated account" << std::endl;
    std::cout << "<wallet>  --> open your local vox wallet page" << std::endl;
    std::cout << "<node>    --> open your local vox FULL NODE DAEMON" << std::endl;
    std::cout << "<remove>  --> erase project vox" << std::endl;
    std::cout << "<server>  --> view server info" << std::endl;
    std::cout << "===========================OPTIONS===========================" << std::endl;
}



int main(int argc, char **argv){
    start();
    
    system("pause");
    return 0;
}
