#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <map>

class xml{
public:
    std::string xml_raw_content;
    std::string tag_name;
    std::string tag_valor;
    std::string xml_file_path;
    //objeto de entrada do arquivo xml
    std::ifstream xml_archive;

    bool open(std::string path){
        xml_archive.open(path);
        xml_file_path = path;

        //verificador de arquivo aberto
        if(!xml_archive.is_open()){
            std::cout << "Failed to open XML archive: " << path << std::endl;
            return false;
        }

        xml_archive >> xml_raw_content;

        //construtor de tags
        build_tags(path);
        build_valors(path);
        return true;
    }

    int xml_size(){
        std::string _data;
        int _archive_size=0;

        xml_archive.open(xml_file_path);

        while(getline(xml_archive, _data)){
            _archive_size += _data.size();
        }

        xml_archive.close();
        return _archive_size;
    }

private:
    void build_tags(std::string path){
        xml_archive.open(path);
        std::string rawdata;

        while(std::getline(xml_archive, rawdata)){
            //variável das posições das tags
            int _left_key_pos;
            int _right_key_pos;

            //variável variativa do nome de uma tag
            std::string _variable_tag_name="";

            if(rawdata.empty()){
                std::cout << "XML archive is empty" << std::endl;
            }

            for(int i=0;i<rawdata.size();i++){
                if(rawdata[i] == '<'){
                    _variable_tag_name = "";
                    _left_key_pos = i;
                }else if(rawdata[i] == '>'){
                    _right_key_pos = i;
                    _variable_tag_name = rawdata.substr(_left_key_pos, _right_key_pos - _left_key_pos + 1); //linha feita por chat GPT
                    tag_name = _variable_tag_name;
                    std::cout << "tag: " << _variable_tag_name << std::endl;
                }
            }
        }
        xml_archive.close();
    }    

    void build_valors(std::string path){
        xml_archive.open(path);
        std::string rawdata;

        while(std::getline(xml_archive, rawdata)){
            //verificador de arquivo xml
            if(rawdata.empty()){
                std::cout << "XML archive is empty" << std::endl;
            }
            //variável das posições das tags
            int _left_key_pos = rawdata.find_first_of('>');
            int _right_key_pos = rawdata.find_last_of('<');

            //variável variativa do valor de uma tag
            std::string _variable_tag_valor="";

            _variable_tag_valor = rawdata.substr(_left_key_pos + 1, _right_key_pos - _left_key_pos - 1);
            tag_valor = _variable_tag_valor;
            std::cout << "valor: " << tag_valor << std::endl;
        }
        xml_archive.close();
    }
};

int main(){
    xml arquivo_de_teste;

    arquivo_de_teste.open("test.xml");
    std::cout << "tamanho do arquivo xml: " << arquivo_de_teste.xml_size() << std::endl;

    //std::cout << arquivo_de_teste.tag_name << std::endl;
    return 1;
}