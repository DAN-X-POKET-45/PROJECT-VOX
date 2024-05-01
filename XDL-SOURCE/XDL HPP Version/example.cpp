#include <iostream>
#include "xdl.hpp"

int main(){
    xdl::file_reader arquivo_de_teste("test.xdl");

    for (const auto& group : arquivo_de_teste.parse()){
        std::cout << "Grupo: " << group.first << std::endl;
        for (const auto& tag : group.second){
            std::cout << "    " << "Chave: " << tag.first << " | " << "Valor: " << tag.second << std::endl;
        }
    }

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.size() << std::endl;
    return 0;
}