#include <initializer_list>
#include <iostream>
#include <variant>
#include <string>
#include <vector>

struct node{
public:
    std::string name;         //tag
    std::string value;        //valor
    std::vector<node> childs; //subnodes

    //construtor para inicializar o nó com nome, valor e filhos
    node(const std::string& name_in, const std::string& value_in, std::initializer_list<node> child_in = {}) : name(name_in), value(value_in), childs(child_in) {}

    //operador [] para acessar um filho pelo nome
    node& operator[](const std::string& key_in) {
        for(auto& child : childs){
            if (child.name == key_in) {
                return child;
            }
        }
        throw std::out_of_range("Child not found");
    }

    bool search_node_child(const std::stirng& node_name){
        for(auto& child_for_search : childs){
            if(child_for_search.name == node_name){
                return true;
            }
        }

        std::cerr << "Node not found! " << '\n' << " Failed to found this node -> " << node_name <<  '\n';
        return false;
    }

    /*bool recursive_child_search(const std::stirng& node_name){
        for(auto& child_for_search : childs){
            if(child_for_search.name == node_name){
                return true;
            }
        }


        std::cerr << "Node not found!" << '\n' << "Failed to found this node -> " << node_name <<  '\n';
        return false;
    }*/

    void change_value(std::string input_value){
        value = input_value;
    }


private:
	typedef std::variant<int, double, bool, char, std::string> data;

};

void print(node node_in, int ident = 0){
    //impressão do nome do nodo
    std::cout << std::string(ident * 2, ' ') << "NODE ID: " << node_in.name << '\n';

    //verificando hierarquia do nodo, se estiver sem valor e com algo dentro do vetor será um subnodo
    if(node_in.childs.size() > 0 && node_in.value.empty() == true){
        std::cout << std::string(ident * 2, ' ') << "NODE CHILDS: " << '\n';
    }else{
        std::cout << std::string(ident * 2, ' ') << "NODE VALOR: " << node_in.value << '\n';
    }

    //impressor recursivo de nodos dentro do vetor de um nodo
    for(const auto& sub_nodes: node_in.childs){
        print(sub_nodes, ident + 1);
    }

    std::cout << '\n';
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
    print(oi);


    std::cout << oi["Toyota"]["op1"].value << '\n';



    return 0;
}
