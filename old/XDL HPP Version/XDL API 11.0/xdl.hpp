#ifndef XDL_HPP_INCLUDED
#define XDL_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <map>

/** 
 * @brief The main namespace of the XDL project
**/
namespace xdl{


    /** 
     * @brief The alias for the type std::map<std::string, std::map<std::string, std::string>>
    **/
    typedef std::map<std::string, std::map<std::string, std::string>> xdl_data_map;

    ///@brief Nothing special
    class info{
    public:
        info();
    };

    /** 
     * @brief file_reader is the consturctor of the file_reader class to initialize a object with the path to the archive for the scan
     * 
     * @param path path_to_archive.xdl
    **/
    class file_reader{
    public:
        //variável para guardar o stream do ifstream do arquivo carregado para leitura de tamanho opicional
        std::string xdl_raw_content;
        //Objeto de entrada do arquivo xdl
        std::ifstream xdl_archive;
        //variável global de acesso ao cainho do arquivo xdl definido no construtor
        std::string xdl_file_path;

        file_reader(std::string path);

        /** 
        * @brief Function to return the size of the object archive
        * @return a int number with the object archive size
        **/
        int size();

        /** 
         * @brief ther XDL code parser
         * @return will return the xdl standard map with the groups, tags, and valors: std::map<std::string, std::map<std::string, std::string>>
        **/
        xdl_data_map parse();
    };

    /** 
     * @brief file_writer is the constructor of the file_writer class to initialize a object with the path to the archive for write in the XDL_MAP content
     * 
     * @brief CAUTION!!! THIS FUNCTION WILL ERASE THE CONTENT IN THE ARCHIVE TARGET AND WRITE NEW CONTENT IN THE FILE
     * 
     * @param path path_to_archive.xdl
     **/
    class file_writer {
    public:
        //Objeto de entrada do arquivo xdl
        std::ofstream xdl_archive;
        //variável global de acesso ao cainho do arquivo xdl definido no construtor
        std::string xdl_file_path;

        file_writer(std::string path);

        /** 
         * @brief CAUTION!!! THIS FUNCTION WILL ERASE THE CONTENT IN THE ARCHIVE TARGET AND WRITE NEW CONTENT IN THE FILE
         * 
         * @param content Put here the XDL _MAP that will be writed in the object file
         **/
        void write(std::map<std::string, std::map<std::string, std::string>> content);

    };

    /** 
     * @brief  XDL map printer, put the xdl map and this function will write the data in the console
     * @param _in_map the xdl map that you want to print
    **/
    void xdl_map_printer(xdl_data_map _in_map);

}

#endif