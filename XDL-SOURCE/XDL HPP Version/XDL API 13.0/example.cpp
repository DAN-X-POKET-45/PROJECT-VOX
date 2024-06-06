#include <iostream>
#include "xdl.hpp"

int main(){
    /*Extensive Definition Language example, version 13.0 | SEXY-DL*/

    //its a "init" for any object that will write and read an XDL archive
    xdl::file_reader arquivo_de_teste("test.xdl");
    xdl::file_writer escrita_de_teste("wright.xdl");

    //it's a printer for xdl data maps
    xdl::xdl_map_printer(arquivo_de_teste.parse());

    xdl::xdl_data_map sales; //lets create a new map

    //Making a Index, Group, Tags, Valors
    sales["sales"]["contoso sales"]["xbox 160"]="15";

    //erasing a tag
    //sales["sales"]["contoso sales"].erase("xbox 160");

    //its a empty tag
    //sales["sales"]["contoso sales"]["xbox 160"];

    xdl::xdl_map_printer(sales);


    //initalizing a XDL map like JSON format
    xdl::xdl_data_map veicles ={
        {"cars", {
            {"BYD", {
                {"PRICE", "1.000$"},
                {"MAXSPEED", "150KM/h"}
            }},
            {"HAVAL", {
                {"PRICE", "3.500$"},
                {"MAXSPEED", "200KM/h"}
            }}
        }},
        {"trucks", {
            {"SCANIA", {
                {"PRICE", "2.350$"},
                {"MAXSPEED", "180KM/h"}
            }},
            {"TESLA", {
                {"PRICE", "5.000$"},
                {"MAXSPEED", "240KM/h"}
            }}
        }}
    };

    xdl::xdl_map_printer(veicles);

    //it will wright the xdl data map on a archive ready to read for other archives
    escrita_de_teste.write(arquivo_de_teste.parse());

    //header example

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.size() << std::endl;
    return 0;
}