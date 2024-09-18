#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "xdl.hpp"

int main(int argc, char **argv){
    /*node oi={"root", "", {
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
    //recursive_print(oi);


    //std::cout << oi["Toyota"]["op1"].get_standard_value() << '\n';

    //oi.print();

    //std::cout << "MALLOCSIZE: " << struct_size(oi) << '\n';

    node ola = {"root", "", {
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
    recursive_print(ola);

    ola.add_child("VOLKS", "razoável");

    recursive_print(ola);

    ola.delete_child("VOLKS");

    recursive_print(ola);
*/

    file_reader oi("test.xdl");
    oi.parse();


    return 0;
}