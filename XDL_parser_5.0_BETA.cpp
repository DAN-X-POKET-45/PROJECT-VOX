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

    class reader{
    public:
        //variável para guardar o stream do ifstream do arquivo carregado para leitura de tamanho opicional
        std::string xdl_raw_content;
        //variável pública do caminho do arquivo
        std::string xdl_file_path;
        //Objeto de entrada do arquivo xdl
        std::ifstream xdl_archive;
        //variáel de armazenamento de dados organizados
        std::map<std::string, std::map<std::string, std::string>> assembled_content;

        //(path to file)Construtor da classe ou string contendo conteúdo do xdl
        reader(std::string path){
            xdl_file_path = path;

            //Abre o arquivo xdl definido no construtor da classe
            xdl_archive.open(path);

            //Verifica se o arquivo foi aberto corretamente
            if (!xdl_archive.is_open()){
                std::cout << "Failed to open XDL archive: " << path << std::endl;
                //Se não puder abrir o arquivo, sai do construtor
                return;
            }

            //Lê o conteúdo bruto do arquivo xdl e repassa a uma variável de conteúdo bruto para verificar se está vazia
            xdl_archive >> xdl_raw_content;

            if(xdl_raw_content.empty()){
                std::cout << "XDL archive is empty" << std::endl;
                return;
            }

            //Fecha o arquivo para ser usado por outras funções
            xdl_archive.close();

            //Constrói os grupos de tags e valores
            std::cout << "assembling: " << path << std::endl;
            parse(path);
            std::cout << path << " assembled finished successfully!!!" << std::endl;
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
        //método de analização lexical do arquivo xdl carregado
        void parse(std::string path){
            xdl_archive.open(path);

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

            //variável variativa de auxílio de verificação de fechamento de grupos
            int group_entry=0;
            
            while(std::getline(xdl_archive, rawdata)){
                //verifica se é um grupo
                if(rawdata.find(':')==std::string::npos && rawdata.find('{')!=std::string::npos){
                    if(group_entry<0){
                        std::cout << "this group-> " << _variable_group_name << " does not closed" << std::endl;
                        xdl_archive.close();
                        return;
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
            return;
            }

            xdl_archive.close();
        }
    };

} //namespace end

int main(){
    XDL::reader arquivo_de_teste("test.xdl");

    std::cout << "tamanho do arquivo XDL: " << arquivo_de_teste.xdl_size() << std::endl;

    for (const auto& group : arquivo_de_teste.assembled_content){ //iterador temporário feito pelo chat GPT
        std::cout << "Grupo: " << group.first << std::endl;
        for (const auto& tag : group.second) {
            std::cout << "  Tag: " << tag.first << " | Valor: " << tag.second << std::endl;
        }
    }

    return 0;
}