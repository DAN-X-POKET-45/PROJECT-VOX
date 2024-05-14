#include <iostream>
#include "xdl.hpp"

int main(){
    //Extensive Definition Language example, version 10.0
    xdl::file_reader arquivo_de_teste("test.xdl");
    xdl::file_writer escrita_de_teste("wright.xdl");

    xdl::xdl_map_printer(arquivo_de_teste.parse());

    xdl::xdl_data_map sales;
    sales["contoso sales"]["xbox 160"]="15";
    xdl::xdl_map_printer(sales);

    
    escrita_de_teste.write(arquivo_de_teste.parse());

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.size() << std::endl;
    return 0;
}