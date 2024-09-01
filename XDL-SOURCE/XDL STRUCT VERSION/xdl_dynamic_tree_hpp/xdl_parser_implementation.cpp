#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "xdl.hpp"

file_reader::file_reader(std::string& path){
    xdl_file_path = path;
}

file_reader::parse(){
    xdl_archive.open(xdl_file_path);

    //Verifica se o arquivo foi aberto corretamente
    if(!xdl_archive.is_open()){
        std::cerr << "Failed to open XDL archive in read mode to return the data: " << xdl_file_path << '\n';
        //Se não puder abrir o arquivo, sai do construtor
        xdl_archive.close();
        std::cerr << "XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
    }

    //tokens de declaração de grupos
    const char LEFT_GROUP_TOKEN = '{';
    const char RIGHT_GROUP_TOKEN = '}';

    //tokens de declaração de chaves
    const char LEFT_KEY_TOKEN = '[';
    const char RIGHT_KEY_TOKEN = ']';

    //declara a linha atual para o getline
    int current_line=1;

    //declaraçao do arquivo de texto (string) bruto para o parser e o assembler
    std::string rawdata;

    //analisador de linhas carregadas dentro da string rawdata
    while(std::getline(xdl_archive, rawdata)){
        
    }


}