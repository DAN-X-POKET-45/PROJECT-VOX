#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

class XDL{
public:
    std::string xdl_raw_content;
    std::string tag_name;
    std::string tag_valor;
    std::string xdl_file_path;
    //Objeto de entrada do arquivo xdl
    std::ifstream xdl_archive;

    //(path to file)Construtor da classe IMPROVISADO PELO CHAT GPT DEVIDO EU NÃO TER CONHECIMETO PARA FAZER ISTO
    XDL(std::string path){
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

        //Fecha o arquivo para ser usado por outra funções
        xdl_archive.close();

        //Constrói as tags e os valores respectivamente dependentes do path
        build_tags(path);
        build_valors(path);
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
    void build_tags(std::string path){
        xdl_archive.open(path);
        std::string rawdata;

        while(std::getline(xdl_archive, rawdata)){
            //variável das posições das tags
            int _left_key_pos;
            int _right_key_pos;

            //variável variativa do nome de uma tag
            std::string _variable_tag_name="";

            if(rawdata.empty()){
                std::cout << "XDL archive is empty" << std::endl;
            }

            for(int i=0;i<rawdata.size();i++){
                if(rawdata[i] == '['){
                    _variable_tag_name = ""; //redefinir a variável dos nomes das tags
                    _left_key_pos = i;
                }else if(rawdata[i] == ']'){
                    _right_key_pos = i;
                    _variable_tag_name = rawdata.substr(_left_key_pos, _right_key_pos - _left_key_pos + 1); //linha feita por chat GPT
                    tag_name = _variable_tag_name;
                    std::cout << "tag: " << _variable_tag_name << std::endl;
                }
            }
        }
        xdl_archive.close();
    }    

    void build_valors(std::string path){
        xdl_archive.open(path);
        std::string rawdata;

        while(std::getline(xdl_archive, rawdata)){
            //verificador de arquivo xdl
            if(rawdata.empty()){
                std::cout << "XDL archive is empty" << std::endl;
            }
            //Variável das posições das tags
            int _left_key_pos = rawdata.find_first_of('>');
            int _right_key_pos = rawdata.find_last_of('<');

            //Variável variativa do valor de uma tag
            std::string _variable_tag_valor="";

            _variable_tag_valor = rawdata.substr(_left_key_pos + 1, _right_key_pos - _left_key_pos - 1);
            tag_valor = _variable_tag_valor;
            std::cout << "valor: " << tag_valor << std::endl;
        }
        xdl_archive.close();
    }
};

int main(){
    XDL arquivo_de_teste("test.xdl");

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.xdl_size() << std::endl;

    //std::cout << arquivo_de_teste.tag_name << std::endl;
    return 1;
}