#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

struct node{
public:
    std::string name;         //tag
    std::string value;        //valor
    std::vector<node> childs; //subnodes

    //construtor para inicializar o nó com nome, valor e filhos
    node(const std::string& name_in, const std::string& value_in, std::initializer_list<node> child_in = {}) : name(name_in), value(value_in), childs(child_in) {}

    //retornador de referência de nodo pelo operador[]
    node& operator[](const std::string& key_in){
        for(auto& child : childs){
            if (child.name == key_in) {
                return child;
            }
        }
        throw std::out_of_range("Child not found");
    }

    //verifiador de existência de nodo
    bool search_node_child(const std::string& node_name){
        for(auto& child_for_search : childs){
            if(child_for_search.name == node_name){
                return true;
            }
        }

        std::cerr << "Node not found! " << '\n' << " Failed to found this node -> " << node_name <<  '\n';
        return false;
    }

/*===================================*/
/*   FUNÇÕES DE CRIAÇÃO E REMOÇAO*/
/*===================================*/




/*===================================*/

    void change_value(std::string input_value){
        value = input_value;
    }

    std::string get_standard_value(){
        return value;
    }


/*===================================*/
/*  FUNÇÕES DE CONVERSÃO DE VALORES*/
/*===================================*/

    //Converter para int
    int get_int_value(){
        try{
            return std::stoi(value);
        }catch(const std::invalid_argument& e){
            std::cerr << "Invalid argument: " << e.what() << '\n';
        }catch(const std::out_of_range& e){
            std::cerr << "Out of range: " << e.what() << '\n';
        }
    }

    //Converter para float
    float get_float_value(){
        try{
            return std::stof(value);
        }catch(const std::invalid_argument& e){
            std::cerr << "Invalid argument: " << e.what() << '\n';
        }catch(const std::out_of_range& e){
            std::cerr << "Out of range: " << e.what() << '\n';
        }
    }

    //Converter para double
    double get_double_value(){
        try{
            return std::stod(value);
        }catch(const std::invalid_argument& e){
            std::cerr << "Invalid argument: " << e.what() << '\n';
        }catch(const std::out_of_range& e){
            std::cerr << "Out of range: " << e.what() << '\n';
        }
    }

    bool get_boolean_value(){
        if(value == "TRUE" || "True" || "true"){
            return true;
        }else if(value == "FALSE" || "False" || "false"){
            return false;
        }else{
            std::cerr << "TYPE ERROR: The value is not correct!" << '\n';
        }
    }

/*===================================*/

    void print(){
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

};


void recursive_print(const node& node_in, int ident = 0){
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

int struct_size(const node& node_in){
    return sizeof(node_in);
}

int main(int argc, char **argv){
    node oi={"root", "", {
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

    oi.print();

    std::cout << "MALLOCSIZE: " << struct_size(oi) << '\n';



    return 0;
}
