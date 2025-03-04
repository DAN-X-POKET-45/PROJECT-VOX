#ifndef XDL_LIB_HPP
#define XDL_LIB_HPP

/*
__  __  ____  _      
\ \/ / |  _ \| |     
 \  /  | | | | |     
 /  \  | |_| | |___  
/_/\_\ |____/|_____|

Extensive Direct Language - megumin
source version: 16.0 
codename: megumin
author: DAN-X POKET 45 (Daniel poket 45)
license: PRIVATE
*/

#include <initializer_list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/**
* @namespace xdl
*
* @brief main namespace of the XDL library, contains all the classes and functions of the library
*/
namespace xdl{
    /**
    * @class node
    *
    * @brief dynamic object for storing and manipulating xdl parsed files and for some other purposes
    */
    class node{
    public:
        std::string name;         //tag
        std::string value;        //valor
        std::vector<node> childs; //subnodes

        //construtor para inicializar o nó com nome, valor e filhos
        node(const std::string& name_in, const std::string& value_in, std::initializer_list<node> child_in = {}) : name(name_in), value(value_in), childs(child_in) {}

        //retornador de referência de nodo pelo operador[] a partir do nome
        node& operator[](const std::string& key_in);

        //retornador de referência de nodo pelo operador[] a partir do índice
        node& operator[](const int& key_index);

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

    /*===================================*/
    /*       FUNÇÕES DE MODIFICAÇÃO      */
    /*===================================*/

        //troca de nome
        void change_name(const std::string& input_name);

        //Troca de valor
        void change_value(const std::string& input_value);

    /*===================================*/



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

        //retornador de valor básico
        std::string get_standard_value();

    /*===================================*/


        //Membro impressor
        void print();

    };



    /*===================================*/
    /*             PARSEADOR             */
    /*===================================*/

    /**
    * @class file_reader
    *
    * @brief the read method of the XDL library, for reading, conversion for strins stream and parsing XDL files
    */
    class file_reader{
    public:
        //variável para guardar o stream bruto do ifstream do arquivo carregado
        std::string xdl_raw_content;
        //Objeto de entrada do arquivo xdl a partir da ifstream
        std::ifstream xdl_archive;
        //variável global de acesso ao caminho do arquivo xdl definido no construtor
        std::string xdl_file_path;

        //construtor
        file_reader(std::string path);

        //parseador
        node parse();

        //conversor para string stream
        std::stringstream convert_to_stringstream();
    private:
        void node_object_assembler(const std::string& name, const std::string& valor, const int& ident);

        /*===================================*/
        /*         OBJETO DE RETORNO         */
        /*===================================*/

        node main_object = {"root",""};

        /*===================================*/

    };

    /*===================================*/



    /*===================================*/
    /*         IMPRESSOR EXTERNO         */
    /*===================================*/

    /**
    * @class file_writer
    *
    * @brief the write method of the XDL library, for writing, conversion for json and exporting XDL Dynamic Objects for files
    */
    class file_writer{
    public:
        //objeto de entrada do arquivo xdl a partir da ofstream para a gravação
        std::ofstream xdl_archive;
        //variável global do caminho domain namespace of the XDL library, contains all the classes and functions of the library arquivo xdl definido no construtor
        std::string xdl_file_path;
        //variável de retorno de fluxo de string para o impressor de string streams
        std::stringstream xdl_ss;

        //construtor
        file_writer(const std::string path);

        //exportador para json
        void export_as_json(const node& content);

        //exportador para XDL
        void export_as_xdl(const node& content);

        //exportador para string stream - fluxo de caractéres
        std::stringstream& export_as_stringstream(const node& content);

    private:
        //impressão recursiva em arquivo json externo
        void json_archive_printer(const node& node_in, int ident);

        //impressão recursiva em arquivo xdl externo
        void xdl_archive_printer(const node& node_in, int ident);

        //impressão recursiva para string stream
        void xdl_string_stream_printer(const node& node_in, int ident);

        
    };

    /*===================================*/



    /*===================================*/
    /*           IMPRESSORES             */
    /*===================================*/

    void recursive_print(const node& node_in, int ident = 0);

    /*===================================*/



    /*===================================*/
    /*            DEPURAÇÃO              */
    /*===================================*/

    int node_size(const node& node_in);

    /*===================================*/



    /*===================================*/
    /*            VALIDADORES            */
    /*===================================*/

    /**
    * @brief checagem de erros de identação
    * 
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * 
    * @return valor booleano que indica erros
    */
    bool check_ident_errors(const std::string& xdl_file_path);

    

    /**
    * @brief checagem de erros de espaçamento entre uma tag e outra
    * 
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * 
    * @return valor booleano que indica erros
    */
    bool check_spacement_errors(const std::string& xdl_file_path);



    /**
    * @brief checagem de erros de sintaxe na criação das tags junto com valores
    * 
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * 
    * @return valor booleano que indica erros
    */
    bool check_tag_syntax_errors(const std::string& xdl_file_path);



    /**
    * @brief checagem de erros de sintaxe na criação de grupos de tags
    * 
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * 
    * @return valor booleano que indica erros
    */
    bool check_group_syntax_errors(const std::string& xdl_file_path);

}



#endif //XDL_LIB_HPP