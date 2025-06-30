#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <xdl.hpp>

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
*/

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


    xdl::file_reader entrada("test.xdl");
    xdl::node test = entrada.parse();

    //xdl::file_writer saida("write.xdl");

    xdl::recursive_print(test);


    std::cout << "-----------------" << '\n';
    std::cout << test["words list"]["words1"]["root"].get_sstream_value().str() << '\n';
    /*
    xdl::log(xdl::log_type::DEBUG, "MAIN", "Testando log de debug");
    xdl::log(xdl::log_type::INFO, "MAIN", "Testando log de info");
    xdl::log(xdl::log_type::WARNING, "MAIN", "Testando log de warning");
    xdl::log(xdl::log_type::ERROR, "MAIN", "Testando log de erro");
    xdl::log(xdl::log_type::CRITICAL, "MAIN", "Testando log de erro crítico");
    */


    //xdl::file_writer tchau("write.xdl");
    //tchau.export_as_xdl(oi.parse());

    /*método de acesso por índice de filhos
    std::cout << test2.childs[0].get_standard_value() << '\n';*/

    return 0;
}