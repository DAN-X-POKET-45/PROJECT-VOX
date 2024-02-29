#include <iostream>
#include <stdlib.h>
//test
void gitupdate(){
    system("cd ~/PROJEECT-VOX");
    system("git pull");
}

void start(){
    std::cout << "=================" << std::endl;
    std::cout << "PROJECT VOX" << std::endl;
    std::cout << "A game by DAN-X" << std::endl;
    std::cout << "=====OPTIONS=====\n\n" << std::endl;
    std::cout << "<update>  --> update project vox game files" << std::endl;
    std::cout << "<version> --> show the current version on your cool gaming PC" << std::endl;
    std::cout << "<launch>  --> launch the game as a NORMAL USER" << std::endl;
    std::cout << "<usercfg> --> open theaccount config page for VOX accounts" << std::endl;
    std::cout << "<you>     --> show your activated account" << std::endl;
    std::cout << "<wallet>  --> open your local vox wallet page" << std::endl;
    std::cout << "<remove>  --> erase project vox" << std::endl;
    std::cout << "<egg>     --> make a egg meme" << std::endl;

}



int main(int argc, char **argv){



    system("pause");
    return 0;
}
