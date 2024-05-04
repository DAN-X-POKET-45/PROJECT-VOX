#include <iostream>
#include "xdl.hpp"

int main(){
    xdl::file_reader arquivo_de_teste("test.xdl");

    xdl::xdl_map_printer(arquivo_de_teste.parse());



    xdl::xdl_data_map sales;
    sales["contoso"]["xbox 160"]="15";
    xdl::xdl_map_printer(sales);

    

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.size() << std::endl;
    return 0;
}