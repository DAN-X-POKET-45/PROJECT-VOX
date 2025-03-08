#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "xdl.hpp"

int main(int argc, char **argv){
    /*xdl::node oi={"root", "", {
                {"BYD", "feio"},
                {"HAVAL", "feio"},
                {"Fiat", "bonitinhos"},
                {"volkswagen","antigo"},
                {"Toyota", "", {
                    {"op1", "não"},
                    {"op2", "sim"}
                    }
                }
            
                }
            }; //Final da inicialização do objeto

    //impressão de objetos
    //xdl::recursive_print(oi);


    //std::cout << oi["Toyota"]["op1"].get_standard_value() << '\n';

    //oi.print();

    //std::cout << "MALLOCSIZE: " << node_size(oi) << '\n';

    xdl::node ola = {"root", "", {
                {"BYD", "feio"},
                {"Toyota", "", {
                    {"op1", "não"},
                    {"op2", "sim"}
                    }
                }
            
                }
            }; //Final da inicialização do objeto

/*
===================================
  TESTE DE MANIPULAÇÃO DE INTENS
===================================
    xdl::recursive_print(ola);

    ola.add_child("VOLKS", "razoável");

    xdl::recursive_print(ola);

    ola.delete_child("VOLKS");

    xdl::recursive_print(ola);
*/


    xdl::file_reader oi("test.xdl");
    std::cout << "main.cpp: pós seleção de caminho de arquivo" << '\n';

    //xdl::node test = oi.parse();

    std::cout << "-----------------" << '\n';

    //xdl::recursive_print(test);

    std::cout << "-----------------" << '\n';

    xdl::file_writer tchau("write.xdl");
    tchau.export_as_xdl(oi.parse());

    /*método de acesso por índice de filhos
    std::cout << test2.childs[0].get_standard_value() << '\n';*/

    return 0;
}