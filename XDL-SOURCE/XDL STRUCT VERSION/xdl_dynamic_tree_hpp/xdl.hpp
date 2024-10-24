#ifndef XDL_DYNAMIC_TREE_OBJECT
#define XDL_DYNAMIC_TREE_OBJECT



#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class node{
public:
    std::string name;         //tag
    std::string value;        //valor
    std::vector<node> childs; //subnodes

    //construtor para inicializar o nó com nome, valor e filhos
    node(const std::string& name_in, const std::string& value_in, std::initializer_list<node> child_in = {}) : name(name_in), value(value_in), childs(child_in) {}

    //retornador de referência de nodo pelo operador[]
    node& operator[](const std::string& key_in);

    //verifiador de existência de nodo
    bool search_node_child(const std::string& node_name);

/*===================================*/
/*   FUNÇÕES DE CRIAÇÃO E REMOÇÃO    */
/*===================================*/

    //Cridor de filhos com valor
    void add_child(const std::string& in_name, const std::string& in_value="");

    //Destruídor de filhos
    void delete_child(const std::string& in_name);


/*===================================*/

    //Troca de valor
    void change_value(std::string input_value);

    std::string get_standard_value();


/*===================================*/
/*  FUNÇÕES DE CONVERSÃO DE VALORES  */
/*===================================*/

    //Converter para int
    int get_int_value();

    //Converter para float
    float get_float_value();

    //Converter para double
    double get_double_value();

    //Verificador e conversor de valor para booleano
    bool get_boolean_value();

/*===================================*/


    //Membro impressor
    void print();

};



/*===================================*/
/*             PARSEADOR             */
/*===================================*/

class file_reader{
public:
    //variável para guardar o stream do ifstream do arquivo carregado
    std::string xdl_raw_content;
    //Objeto de entrada do arquivo xdl a partir da ifstream
    std::ifstream xdl_archive;
    //variável global de acesso ao caminho do arquivo xdl definido no construtor
    std::string xdl_file_path;

    //construtor
    file_reader(std::string path);

    //parseador
    node parse();
private:
    void node_object_assembler(const std::string& name, const std::string& valor, node& node_in);

    /*===================================*/
    /*         OBJETO DE RETORNO         */
    /*===================================*/

    node main_object = {"root",""};

    /*===================================*/

};

/*===================================*/



void recursive_print(const node& node_in, int ident = 0);

int node_size(const node& node_in);



#endif //XDL_DYNAMIC_TREE_OBJECT