#include <iostream>
#include <string>

#include <vector>
#include <variant>
#include <map>

struct xdlelement{
    int element_line;
    std::string element_name;
    std::string element_type;
    std::vector<xdlelement> content;
};

// Função para imprimir a estrutura de um elemento
void printElement(const xdlelement &element, int indent = 0){
    std::string indentStr(indent, ' ');
    std::cout << indentStr << "Line: " << element.element_line << "\n";
    std::cout << indentStr << "Name: " << element.element_name << "\n";
    std::cout << indentStr << "Type: " << element.element_type << "\n";
    std::cout << indentStr << "Content:\n";
    for (const auto &child : element.content){
        printElement(child, indent + 2);
    }
}

int main(){
    xdlelement cont = {0, "root", "índice", {{1, "seeds", "group", {}}, {2, "seeds", "não", {}}}};
    printElement(cont);

    return 0;
}
