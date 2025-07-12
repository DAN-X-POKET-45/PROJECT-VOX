#ifndef XDL_LIB_HPP
#define XDL_LIB_HPP

/*
__  __  ____  _      
\ \/ / |  _ \| |     
 \  /  | | | | |     
 /  \  | |_| | |___  
/_/\_\ |____/|_____|

Extensive Direct Language - megumin
source version: 17.0 
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
        /**
         * @brief name of this node
         */
        std::string name;         //tag

        /**
         * @brief value of this node
         */
        std::string value;        //valor

        /**
         * @brief childs of this node
         */
        std::vector<node> childs; //subnodes

        /**
         * @brief default constructor
         * @param name_in the name of the node
         * @param value_in the value of the node
         * @param child_in the child nodes of the node
         * @note you can build a entire node form this constrcutor in the code
         */
        node(const std::string& name_in, const std::string& value_in, std::initializer_list<node> child_in = {}) : name(name_in), value(value_in), childs(child_in) {}

        /**
         * @brief reference returner from the name of the child node
         * @param key_in the name of the child node
         * @return node - the reference of the child node
         */
        node& operator[](const std::string& key_in);

        /**
         * @brief reference returner from the index of the child node
         * @param key_index the index of the child node
         * @return node - the reference of the child node
         */
        node& operator[](unsigned const int& key_index);

        /**
         * @brief search for a node by name
         * @param node_name the name of the node to be searched
         * @return node - if found return true if not found return false
         */
        bool search_node_child(const std::string& node_name);

    /*===================================*/
    /*   FUNÇÕES DE CRIAÇÃO E REMOÇÃO    */
    /*===================================*/

        /**
         * @brief add a child to the node
         * @param in_name the name of the child
         * @param in_value the value of the child
         */
        void add_child(const std::string& in_name, const std::string& in_value="");

        /**
         * @brief delete a child from the node
         * @param in_node the node name to be deleted
         */
        void delete_child(const std::string& in_name);


    /*===================================*/

    /*===================================*/
    /*       FUNÇÕES DE MODIFICAÇÃO      */
    /*===================================*/

        /**
         * @brief change the name of the node
         * @param input_name the new name of the node
         */
        void change_name(const std::string& input_name);

        /**
         * @brief change the value of the node
         * @param input_value the new value of the node
         */
        void change_value(const std::string& input_value);

    /*===================================*/



    /*===================================*/
    /*  FUNÇÕES DE CONVERSÃO DE VALORES  */
    /*===================================*/

        /**
         * @brief convert the value and return the int value of the node
         * @return int - the int value converted
         */
        int get_int_value();

        /**
         * @brief convert the value and return the float value of the node
         * @return float - the float value converted
         */
        float get_float_value();

        /**
         * @brief convert the value and return the double value of the node
         * @return double - the double value converted
        */
        double get_double_value();

        /**
         * @brief convert the value and return the boolean value of the node
         * @return bool - the boolean value converted
         */
        bool get_boolean_value();

        /**
         * @brief get the standard std::string value of the node
         * @return std::string - the standard value of the node
         */
        std::string get_standard_value();

        /**
         * @brief convert the value and return the std::stringstream value of the node
         * @return std::stringstream - the std::stringstrem value converted
         */
        std::stringstream get_sstream_value();

    /*===================================*/


        /**
         * @brief print all info of the node
         */
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
        /**
         * @brief the raw content of the xdl file
         */
        std::string xdl_raw_content;

        /**
         * @brief the input xdl file
         */
        std::ifstream xdl_archive;

        /**
         * @brief the path to the xdl file
         */
        std::string xdl_file_path;



        /**
         * @brief construtor
         * @param path the path to the file to be read
         */
        file_reader(std::string path);

        /**
         * @brief parse the entire xdl file and return the root node
         * @return root node - the root node of the xdl file parsed
         */
        node parse();

        /**
         * @brief convert the entire xdl file to a string stream
         * @return std::stringstream - the string stream with the content
         */
        std::stringstream convert_to_stringstream();
    private:
        void node_object_assembler(const std::string& name, const std::string& valor, unsigned const int& ident);

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
        /**
         * @brief xdl file to be written
         */
        std::ofstream xdl_archive;

        /**
         * @brief path to the xdl file to be written
         */
        std::string xdl_file_path;

        /**
         * @brief store the content of the xdl file to be written in a string stream used by export_as_stringstream()
         */
        std::stringstream xdl_ss;

        /**
         * @brief construtor
         * @param path the path to the file to be written - NULL VALUE just in STRING STREAM EXPORT
         */
        file_writer(const std::string path);

        /**
         * @brief export a entire node to an existing or new JSON file in the file system
         * @param content the node to make the export as JSON file
         */
        void export_as_json(const node& content);

        /**
         * @brief export a entire node to an existing or new xdl  file in the file system
         * @param content the node to make the export as xdl file
         */
        void export_as_xdl(const node& content);

        /**
         * @brief export a entire node to a string stream
         * @param node the node to make the export as string stream similiar to an archive
         * @return std::stringstream& - the string stream with the content
         */
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


    /**
     * @brief print all nodes inside a node with all information
     */
    void recursive_print(const node& node_in, int ident = 0);

    /*===================================*/



    /*===================================*/
    /*          DEPURAÇÃO E LOGS         */
    /*===================================*/

    /**
     * @brief log type enum
     * @details This enum is used to define the type of log that will be printed or returned
     * DEBUG - for debug messages 
     * INFO - for information messages
     * WARNING - for warning messages
     * ERROR - for error messages
     * CRITICAL - for critical error messages
     */
    enum class log_type{
        ///@brief log type for debug messages, print in std::cout
        DEBUG,
        ///@brief log type for information messages, print in std::cout
        INFO,
        ///@brief log type for warning messages, print in std::cerr
        WARNING,
        ///@brief log type for error messages, print in std::cerr
        ERROR,
        ///@brief log type for critical error messages, print in std::cerr
        CRITICAL
    };

    /**
     * @brief log with print in std::cout or std::cerr
     * @param type the type of the log (see @ref xdl::log_type enum)
     * @param specification the specification of the log
     * @param message the message of the log
     * @return std::string - the log message as a string
     */
    void log(log_type type, const std::string& specification, const std::string& message);

    /**
     * @brief log with return as string
     * @param type the type of the log (see log_type enum)
     * @param specification the specification of the log
     * @param message the message of the log
     * @param return_as_str if true, return the log as a string, if false, return [...] to hide the log content but identify that had a log there
     * @return std::string - the log message as a string
     */
    std::string log(log_type type, const std::string& specification, const std::string& message, bool return_as_str);

    /**
     * @brief basic size analizer
     */
    int node_size(const node& node_in);

    /*===================================*/



    /*===================================*/
    /*            VALIDADORES            */
    /*===================================*/

    /**
    * @brief checagem de erros de identação
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * @return valor booleano que indica erros
    */
    bool check_ident_errors(const std::string& xdl_file_path);

    

    /**
    * @brief checagem de erros de espaçamento entre uma tag e outra
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * @return valor booleano que indica erros
    */
    bool check_spacement_errors(const std::string& xdl_file_path);



    /**
    * @brief checagem de erros de sintaxe na criação das tags junto com valores
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * @return valor booleano que indica erros
    */
    bool check_tag_syntax_errors(const std::string& xdl_file_path);



    /**
    * @brief checagem de erros de sintaxe na criação de grupos de tags
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * @return valor booleano que indica erros
    */
    bool check_group_syntax_errors(const std::string& xdl_file_path);



    /**
    * @brief checagem de erros de sintaxe em blocos e linhas de comentários
    * @param raw_input_data fluxo de entrada de dados de um arquivo ou string com conteúdo bruto
    * @return valor booleano que indica erros
    */
    bool check_comment_syntax_errors(const std::string& xdl_file_path);

}



#endif //XDL_LIB_HPP