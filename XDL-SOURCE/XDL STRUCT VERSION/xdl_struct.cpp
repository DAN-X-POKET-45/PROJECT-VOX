#include <initializer_list>
#include <iostream>
#include <variant>
#include <string>
#include <vector>

// Definimos a estrutura Node
struct node{
public:
    std::string name;         //tag
    std::string value;        //valor
    std::vector<node> childs; //subnodes

    // Construtor para inicializar o nó com nome, valor e filhos
    node(const std::string& name_in, const std::string& value_in, std::initializer_list<node> child_in = {}) : name(name_in), value(value_in), childs(child_in) {}

    std::string operator[](const std::string& key_in) {
        for(const auto& child : childs){
            if(child.name == key_in){
                return child.value;
            }
        }
        return node(&childs;
    }

private:
	typedef std::variant<int, double, bool, char, std::string, node> data;

};

void print(node node_in, int ident = 0){
    //impressão do nome do nodo
    std::cout << std::string(ident * 2, ' ') << "NODE ID: " << node_in.name << '\n';

    //verificando hierarquia do nodo, se estiver sem valor e com algo dentro do vetor será um subnodo
    if(node_in.childs.size() > 0 && node_in.value.empty() == true){
        std::cout << "NODE CHILDS: " << '\n';
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
    node oi = {"carros", "", {
            {"BYD", "feio"},
            {"HAVAL", "feio"},
            {"Fiat", "bonitinhos"},
            {"volkswagen","antigo"}
        }
    }; //Final da inicialização do objeto
    
    std::cout << oi["André"] << '\n';

    //impressão de objetos
    print(oi);



    return 0;
}
