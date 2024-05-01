#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <map>

namespace XDL{
    class info{
    public:
    info(){
        //declarador de dados da versão compilada atual do XDL no qual dno momento dve ser inútil dentro do arquivo
        const std::string version="5.0";
        const std::string description="XDL is a local databank to sotore data in single containers or archives created to store tridimensional data for game saves/imports/exports";
        const std::string arch="AMD-64";
        const std::string encode="UTF-8";
        const std::string mode="read-only";
        const std::string dependencies="VOX-CORE";
        const std::string codename="WIFU-DL";
        const std::string developer="DAN-X";
        const std::string madein="POSITIVO STILO (H14BT58) 2013-NOW";
        const std::string secure_mode="enabled";
        const std::string license="PROJECT-VOX team licensed by DAN-X, the creator";
        }
    };

    class file_reader{
    public:
        //variável para guardar o stream do ifstream do arquivo carregado para leitura de tamanho opicional
        std::string xdl_raw_content;
        //Objeto de entrada do arquivo xdl
        std::ifstream xdl_archive;



        //(path to file)Método para obter o tamanho do arquivo xdl
        int xdl_size(std::string path){
            std::string _data;
            int _archive_size=0;

            xdl_archive.open(path);

            //Verifica se o arquivo foi aberto corretamente
            if (!xdl_archive.is_open()){
                std::cout << "Failed to open XDL archive in read mode: " << path << std::endl;
                //Se não puder abrir o arquivo, sai do construtor
            }

            while(getline(xdl_archive, _data)){
                _archive_size += _data.size();
            }

            xdl_archive.close();
            return _archive_size;
        }

        //método de analização lexical do arquivo xdl carregado
        std::map<std::string, std::map<std::string, std::string>> parse(std::string path){
            xdl_archive.open(path);

            //Verifica se o arquivo foi aberto corretamente
            if (!xdl_archive.is_open()){
                std::cout << "Failed to open XDL archive in read mode: " << path << std::endl;
                //Se não puder abrir o arquivo, sai do construtor
            }

            //declara a linha atual para o getline
            int current_line=1;

            //declaraçao do arquivo de texto bruto para o analisador
            std::string rawdata;

            //variável variativa do nome de uma tag
            std::string _variable_tag_name="";

            //Variável variativa do valor de uma tag
            std::string _variable_tag_valor="";

            //Variável variativa do nome de um grupo de tags e valores
            std::string _variable_group_name="";

            //variáel de armazenamento de dados organizados
            std::map<std::string, std::map<std::string, std::string>> assembled_content;

            //variável variativa de auxílio de verificação de fechamento de grupos
            int group_entry=0;
            
            while(std::getline(xdl_archive, rawdata)){
                //verifica se é um grupo
                if(rawdata.find(':')==std::string::npos && rawdata.find('{')!=std::string::npos){
                    if(group_entry<0){
                        std::cout << "this group-> " << _variable_group_name << " does not closed" << std::endl;
                        xdl_archive.close();
                    }

                    int _group_name_right_pos = rawdata.find_first_of('{');

                    //indica que o grupo está aberto
                    group_entry--;

                    //organizador de grupo
                    _variable_group_name = rawdata.substr(0, _group_name_right_pos);

                    //impressor/anexador de emergência de teste de grupos
                    //std::cout << "GRUPO: " << _variable_group_name << std::endl;
                }

                //verifica se é uma tag
                if(rawdata.find(':')!=std::string::npos && rawdata.find('[')!=std::string::npos && rawdata.find(']')!=std::string::npos && rawdata.find('{')==std::string::npos) {
                    int _left_key_pos = rawdata.find_first_of('[');
                    int _right_key_pos = rawdata.find_last_of(']');
                    int _two_point_pos = rawdata.find_first_of(':');              

                    //organizador e atribuidor de tags
                    _variable_tag_name = rawdata.substr(_left_key_pos + 1, _two_point_pos - _left_key_pos - 1);

                    //organizador e atribuidor de valores
                    _variable_tag_valor = rawdata.substr(_two_point_pos + 1, _right_key_pos - _two_point_pos - 1);

                    //impressor/anexador de valores e tags
                    //std::cout << "    " << "tag...: " << _variable_tag_name << std::endl;
                    //std::cout << "    " <<"valor.: " << tag_valor << std::endl << std::endl;

                    //montador de dados xdl
                    assembled_content[_variable_group_name][_variable_tag_name]=_variable_tag_valor;
                }

                if(rawdata.find('}')!=std::string::npos){
                    //fecha o grupo de tags
                    group_entry++;
                }
            }

            if(group_entry<0){
            std::cout << "this group-> " << _variable_group_name << " does not closed" << std::endl;
            xdl_archive.close();            
            }

            //fecha o arquivo
            xdl_archive.close();

            //finalização e envio do resultado
            std::cout << path << " assembled!" << std::endl;
            return assembled_content;
        }
    };

    class file_writer{
    public:
        //Objeto de entrada do arquivo xdl
        std::ofstream xdl_archive;

        //(xdlmap to write, path to file) método de escritutra
        void write(std::map<std::string, std::map<std::string, std::string>> content, std::string path){
            //Abre o arquivo xdl definido no construtor da classe
            xdl_archive.open(path);

            if (!xdl_archive.is_open()){
                std::cout << "Failed to open XDL archive in wright mode: " << path << std::endl;
                //Se não puder abrir o arquivo, sai do construtor
                return;
            }

            //tokens de declaração de grupos
            const char LEFT_GROUP_TOKEN = '{';
            const char RIGHT_GROUP_TOKEN = '}';

            //tokens de declaração de chaves
            const char LEFT_KEY_TOKEN = '[';
            const char RIGHT_KEY_TOKEN = ']';

            //token de declarador de valor
            const char ASSEMBLER_TOKEN = ':';

            //impressor
            for (const auto& group : content){
                std::cout << group.first << LEFT_GROUP_TOKEN << std::endl;
                for (const auto& tag : group.second){
                    std::cout << "    " << LEFT_KEY_TOKEN << tag.first << ASSEMBLER_TOKEN << tag.second << RIGHT_KEY_TOKEN << std::endl;
                }
                std::cout << RIGHT_GROUP_TOKEN << std::endl;
            }

            //fecha o arquivo
            xdl_archive.close();

            //mostra que foi concluído com sucesso
            std::cout << "content writed in: " << path << std::endl; 
        }
    };

} //namespace end

int main(){
    XDL::file_reader arquivo_de_teste;

    XDL::file_writer escrita_de_teste;

    escrita_de_teste.write(arquivo_de_teste.parse("test.xdl"), "wright.xdl");

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.xdl_size("test.xdl") << std::endl;

    return 0;
}