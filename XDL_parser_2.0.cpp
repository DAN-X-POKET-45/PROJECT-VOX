#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

namespace XDL{
    class info{
    info(){
        //declarador de dados da versão compilada atual do XDL
        const std::string version="2.0";
        const std::string description="XDL is a local databank to sotore data in single containers or archives created to store tridimensional data for game saves/imports/exports";
        const std::string arch="AMD-64";
        const std::string encode="UTF-8";
        const std::string mode="read-only";
        const std::string dependencies="VOX-CORE";
        const std::string codename="SEXY-DL";
        const std::string developer="DAN-X";
        const std::string madein="POSITIVO STILO (H14BT58) 2013-NOW";
        const std::string secure_mode="disabled";
        const std::string license="PROJECT-VOX team licensed by DAN-X, teh creator";
        }
    };

    class file{
    public:
        std::string xdl_raw_content;
        std::string tag_name;
        std::string tag_valor;
        std::string xdl_file_path;
        //Objeto de entrada do arquivo xdl
        std::ifstream xdl_archive;

        //(path to file)Construtor da classe ou string contendo conteúdo do xdl
        file(std::string path){
            xdl_file_path = path;

            //Abre o arquivo xdl definido no construtor da classe
            xdl_archive.open(path);

            //Verifica se o arquivo foi aberto corretamente
            if (!xdl_archive.is_open()){
                std::cout << "Failed to open XDL archive: " << path << std::endl;
                //Se não puder abrir o arquivo, sai do construtor
                return;
            }

            //Lê o conteúdo bruto do arquivo xdl e repassa a uma variável de conteúdo bruto
            xdl_archive >> xdl_raw_content;

            if(xdl_raw_content.empty()){
                std::cout << "XDL archive is empty" << std::endl;
                return;
            }

            //Fecha o arquivo para ser usado por outra funções
            xdl_archive.close();

            //Constrói as tags e os valores respectivamente dependentes do path
            parse(path);
        }

        //Método para obter o tamanho do arquivo xdl
        int xdl_size(){
            std::string _data;
            int _archive_size=0;

            xdl_archive.open(xdl_file_path);

            while(getline(xdl_archive, _data)){
                _archive_size += _data.size();
            }

            xdl_archive.close();
            return _archive_size;
        }

    private:
        void parse(std::string path){
            xdl_archive.open(path);

            //declaraçao do arquivo de texto bruto para o analisador
            std::string rawdata;

            //variável variativa do nome de uma tag
            std::string _variable_tag_name="";

            //Variável variativa do valor de uma tag
            std::string _variable_tag_valor="";
            
            while(std::getline(xdl_archive, rawdata)){
                //indentificadores de posição dos caracteres de declaração
                int _left_key_pos = rawdata.find_first_of('[');
                int _right_key_pos = rawdata.find_last_of(']');
                int _two_point_pos = rawdata.find_first_of(':');

                //organizador e atribuidor de tags
                _variable_tag_name = rawdata.substr(_left_key_pos + 1, _two_point_pos - _left_key_pos - 1);
                tag_name = _variable_tag_name;

                //organizador e atribuidor de valores
                _variable_tag_valor = rawdata.substr(_two_point_pos + 1, _right_key_pos - _two_point_pos - 1);
                tag_valor = _variable_tag_valor;

                //impressor de valores e tags
                std::cout << "tag...: " << _variable_tag_name << std::endl;
                std::cout << "valor.: " << tag_valor << std::endl << std::endl;
            }
            xdl_archive.close();
        }    
    };

} //namespace end

int main(){
    XDL::file arquivo_de_teste("test.xdl");

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.xdl_size() << std::endl;

    //std::cout << arquivo_de_teste.tag_name << std::endl;
    return 1;
}