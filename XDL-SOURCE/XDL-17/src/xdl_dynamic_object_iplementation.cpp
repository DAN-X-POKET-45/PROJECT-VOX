#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "xdl.hpp"



namespace xdl{
    //retornador de referência de nodo pelo operador[] a partir do nome
    node& node::operator[](const std::string& key_in){
        for(auto& child : childs){
            if(child.name == key_in) {
                return child;
            }
        }
        throw std::out_of_range(std::string("\033[31m[XDL-NODE RETURNING ERROR!]\033[0m") + " \"" + key_in + "\" - " + "Child not found!");
    }

    //retornador de referência de nodo pelo operador[] a partir do índice
    node& node::operator[](unsigned const int& key_index){
        if(key_index < 0 || key_index >= childs.size()){
            throw std::out_of_range(std::string("\033[31m[XDL-NODE RETURNING ERROR!]\033[0m") + " \"" + std::to_string(key_index) + "\" - " + "index does not match the object vector");
        }else{
            return childs[key_index];
        }
    }

    //verificador de existência de nodo
    bool node::search_node_child(const std::string& node_name){
        for(const auto& child_for_search : childs){
            if(child_for_search.name == node_name){
                return true;
            }
        }

        std::cerr << "\033[31m[XDL-NODE NODE_SEARCH ERROR!]\033[0m Node not found! Failed to found this node -> " << node_name <<  '\n';
        return false;
    }

    /*===================================*/
    /*   FUNÇÕES DE CRIAÇÃO E REMOÇAO    */
    /*===================================*/

    //Cridor de filhos com valor
    void node::add_child(const std::string& in_name, const std::string& in_value){
        if(name.empty()){
            std::cerr << "\033[31m[XDL-NODE ADD_CHILD ERROR!]\033[0m Error in child creating! Name is empty" << '\n';
        }
        childs.push_back(node(in_name, in_value));
    }

    //Destruídor de filhos
    void node::delete_child(const std::string& in_name){
        size_t index = 1;
        for(const auto& child_for_search : childs){
            if(child_for_search.name == in_name){
                childs.erase(childs.begin() + index);
            }else{
                index++;
            }
        }
    }


    /*===================================*/

    //troca de nome
    void node::change_name(const std::string& input_name){
        name = input_name;
    }

    //Troca de valor
    void node::change_value(const std::string& input_value){
        value = input_value;
    }

    //retorno de valor em formato de string
    std::string node::get_standard_value(){
        return value;
    }

    //retorno de valor em formato de stringstream
    std::stringstream node::get_sstream_value(){
        std::stringstream sstream_value;
        sstream_value << value;
        return sstream_value;
    }


    /*===================================*/
    /*  FUNÇÕES DE CONVERSÃO DE VALORES  */
    /*===================================*/

    //Converter para int
    int node::get_int_value(){
        try{
            return std::stoi(value);
        }catch(const std::invalid_argument& e){
            std::cerr << "\033[31m[XDL-NODE STOI ERROR!]\033[0m Invalid argument: " << e.what() << '\n';
        }catch(const std::out_of_range& e){
            std::cerr << "\033[31m[XDL-NODE STOI ERROR!]\033[0m Out of range: " << e.what() << '\n';
        }

        //retorno de erro
        return 0;
    }

    //Converter para float
    float node::get_float_value(){
        try{
            return std::stof(value);
        }catch(const std::invalid_argument& e){
            std::cerr << "\033[31m[XDL-NODE STOF ERROR!]\033[0m Invalid argument: " << e.what() << '\n';
        }catch(const std::out_of_range& e){
            std::cerr << "\033[31m[XDL-NODE STOF ERROR!]\033[0m Out of range: " << e.what() << '\n';
        }

        //retorno de erro
        return 0.0f;
    }

    //Converter para double
    double node::get_double_value(){
        try{
            return std::stod(value);
        }catch(const std::invalid_argument& e){
            std::cerr << "\033[31m[XDL-NODE STOD ERROR!]\033[0m Invalid argument: " << e.what() << '\n';
        }catch(const std::out_of_range& e){
            std::cerr << "\033[31m[XDL-NODE STOD ERROR!]\033[0m Out of range: " << e.what() << '\n';
        }

        //retorno de erro
        return 0.0;;
    }

    //Verificador e conversor de valor para booleano
    bool node::get_boolean_value(){
        if(value == "TRUE" || "True" || "true"){
            return true;
        }else if(value == "FALSE" || "False" || "false"){
            return false;
        }else{
            std::cerr << "\033[31m[XDL-NODE STOB ERROR!]\033[0m TYPE ERROR: The value is not correct!" << '\n';
        }

        //retorno de erro
        return false;
    }

    /*===================================*/


    //Membro impressor
    void node::print(){
        std::cout << "==============" << "INFO" << "==============" << '\n';
        std::cout << "Node name  -> " << name << '\n'; //Impressor de nome

        if(value.empty() == true){ //se não tiver um valor fala que não tem valor
            std::cout << "Node valor -> " << "EMPTY" << '\n';
        }else{
            std::cout << "Node valor -| " << value << '\n'; //se não estiver vazio imprime o valor
        }

        if(childs.size() > 0){ //se tiver filhos imprime os filhos
            std::cout << "Node child -> " << '\n';

            for(const auto& sub_node : childs){
                //declarador de tipo
                std::string type;

                if(sub_node.childs.size() > 0 && sub_node.value.empty() == true){ //se tiver apenas filhos sem uma árvore
                    type = "TREE";
                }else if(sub_node.childs.size() == 0 && sub_node.value.empty() == true){ //se estiver vazio
                    type = "EMPTY";
                }else{
                    type = "VALOR";
                }

                std::cout << "  " << sub_node.name << " -> " << type << '\n';
            }
        }else{ //se não tiver filhos fala que não tem filhos
            std::cout << "Node child -> " << "EMPTY" << '\n';
        }

        std::cout << "================================" << '\n';
    }


    /*EXCETOS!!!*/

    //Impressão recursiva
    void recursive_print(const node& node_in, int ident){
        //impressão do nome do nodo
        std::cout << std::string(ident * 2, ' ') << "NODE NAME: " << node_in.name << '\n';

        //verificando hierarquia do nodo, se estiver sem valor e com algo dentro do vetor será um subnodo
        if(node_in.childs.size() > 0 && node_in.value.empty() == true){
            std::cout << std::string(ident * 2, ' ') << "NODE CHILD: " << '\n';
        }else{
            std::cout << std::string(ident * 2, ' ') << "NODE VALOR: " << node_in.value << '\n';
        }

        //impressor recursivo de nodos dentro do vetor de um nodo
        for(const auto& sub_nodes : node_in.childs){
            recursive_print(sub_nodes, ident + 1);
        }

        std::cout << '\n';
    }

    //Cálculo básico de tamanho do objeto nodo
    int node_size(const node& node_in){
        return sizeof(node_in);
    }

}