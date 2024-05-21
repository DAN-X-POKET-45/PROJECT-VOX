#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "xdl.hpp"

namespace xdl{
    info::info(){
        //declarador de dados da versão compilada atual do XDL no qual dno momento dve ser inútil dentro do arquivo
        const std::string version="12.0";
        const std::string description="XDL is a local databank to store data in single containers inside a index or archives created to store anything like a strings or ints, including data structures";
        const std::string arch="AMD-64";
        const std::string encode="UTF-8";
        const std::string mode="Read and Write, and this is so right";
        const std::string dependencies="NOTHING SPECIAL!";
        const std::string codename="VIX-DL";
        const std::string developer="DAN-X";
        const std::string madein="VSCODE and NANO in POSITIVO STILO (H14BT58) 2013-NOW";
        const std::string secure_mode="enabled";
        const std::string headers="return a struct";
        const std::string license="PROJECT-VOX team licensed by DAN-X, the creator";
    }

    //(file to path) construtor da classe de leitura de grupo de dados XDL
    file_reader::file_reader(std::string path){
        xdl_file_path = path;
    }

    //Método para obter o tamanho do arquivo xdl
    int file_reader::size(){
        std::string _data;
        int _archive_size=0;

        xdl_archive.open(xdl_file_path);

        //Verifica se o arquivo foi aberto corretamente
        if (!xdl_archive.is_open()){
            std::cerr << "Failed to open XDL archive in read mode to get the archive size: " << xdl_file_path << std::endl;
            //Se não puder abrir o arquivo, sai do construtor
            xdl_archive.close();
            std::cerr << "XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
        }

        while(getline(xdl_archive, _data)){
            _archive_size += _data.size();
        }

        xdl_archive.close();
        return _archive_size;
    }

    //método de montagem e retorno de XDL-map
    xdl_data_map file_reader::parse(){
        xdl_archive.open(xdl_file_path);

        //Verifica se o arquivo foi aberto corretamente
        if (!xdl_archive.is_open()){
            std::cerr << "Failed to open XDL archive in read mode to return the data: " << xdl_file_path << std::endl;
            //Se não puder abrir o arquivo, sai do construtor
            xdl_archive.close();
            std::cerr << "XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
        }

        //declara a linha atual para o getline
        int current_line=1;

        //declaraçao do arquivo de texto bruto para o analisador
        std::string rawdata;

        //variável variativa do nome de um índice
        std::string _variable_index_name="";

        //variável variativa do nome de uma tag
        std::string _variable_tag_name="";

        //Variável variativa do valor de uma tag
        std::string _variable_tag_valor="";

        //Variável variativa do nome de um grupo de tags e valores
        std::string _variable_group_name="";

        //variáel de armazenamento de dados organizados
        xdl_data_map assembled_content;

        //variável variativa de auxílio de verificação de fechamento de grupos
        int group_entry=0;

        //variável variativa de auxílio de verificação de fechamento de indíces
        int index_entry=0;
            
        while(std::getline(xdl_archive, rawdata)){
            //verifica se é um índice
            if(rawdata.find(':')==std::string::npos && rawdata.find('{')!=std::string::npos && rawdata.find_first_of(' ')!=0){
                if(index_entry<0){
                    //se encontrar outro índice aberto o parseamento é parado
                    std::cerr << "This index-> " << _variable_index_name << "in line: " << current_line << " does not closed!!!" << std::endl;
                    xdl_archive.close();
                    std::cerr << "XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
                }       

                int _index_name_right_pos = rawdata.find_first_of('{');

                //indica que o índice está aberto
                index_entry--;

                //organizador de índices
                _variable_index_name = rawdata.substr(0, _index_name_right_pos);

                //impressor/anexador de emergência de teste de índices
                //std::cout << "ÍNDICE: " << _variable_group_name << std::endl;
            }

            //verifica se é um grupo
            if(rawdata.find(':')==std::string::npos && rawdata.find('{')!=std::string::npos && rawdata.find_first_of(' ')==0){
                if(group_entry<0){
                    std::cerr << "This group-> " << _variable_group_name << "in line: " << current_line << " does not closed!!!" << std::endl;
                    xdl_archive.close();
                    std::cerr << "XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
                }

                int _group_name_right_pos = rawdata.find_first_of('{');
                //variável para detectar o último espaço em branco antes do nome do grupo para evitar que o nome do grupo seja um espaço em branco
                int indentation_guard = rawdata.find_first_not_of(' ');

                //indica que o grupo está aberto
                group_entry--;

                //organizador de grupo
                _variable_group_name = rawdata.substr(indentation_guard, (_group_name_right_pos - indentation_guard));

                //impressor/anexador de emergência de teste de grupos
                //std::cout << "    " << "GRUPO: " << _variable_group_name << std::endl;
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
                //std::cout << "    " << "    " << "tag...: " << _variable_tag_name << std::endl;
                //std::cout << "    " << "    " << "valor.: " << tag_valor << std::endl << std::endl;

                //montador de dados xdl
                assembled_content[_variable_index_name][_variable_group_name][_variable_tag_name]=_variable_tag_valor;
            }

            if(rawdata.find('}')!=std::string::npos){
                //fecha o grupo de tags
                group_entry++;
            }

            if(rawdata.find('}')!=std::string::npos && rawdata.find_first_of(' ')!=0){
                //fecha um índice
                index_entry++;
            }

            std::cout << "Line-> " << current_line << "readed!" << '\n';
            current_line++;
        }
        //fecha o arquivo
        xdl_archive.close();

        //finalização e envio do resultado
        std::cout << xdl_file_path << " assembled!" << std::endl;
        return assembled_content;
    }
    
    //(XDL-map to write in a archive) construtor da classe de estrutura de escrita
    file_writer::file_writer(std::string path){
        xdl_file_path = path;
    }

    //método de escritura
    void file_writer::write(xdl_data_map content){
        //Abre o arquivo xdl definido no construtor da classe
        xdl_archive.open(xdl_file_path);

        if (!xdl_archive.is_open()){
            std::cerr << "Failed to open XDL archive in wright mode: " << xdl_file_path << std::endl;
            //Se não puder abrir o arquivo, sai do construtor
            xdl_archive.close();
            std::cerr << "XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
        }

        //tokens de declaração de grupos
        const char LEFT_GROUP_TOKEN = '{';
        const char RIGHT_GROUP_TOKEN = '}';

        //tokens de declaração de índices (repetido)
        const char LEFT_INDEX_TOKEN = '{';
        const char RIGHT_INDEX_TOKEN = '}';

        //tokens de declaração de chaves
        const char LEFT_KEY_TOKEN = '[';
        const char RIGHT_KEY_TOKEN = ']';

        //token de declarador de valor
        const char ASSEMBLER_TOKEN = ':';

        //impressor
        for(const auto& index : content){
            xdl_archive << index.first << LEFT_INDEX_TOKEN << '\n';
            for (const auto& group : index.second){
                xdl_archive << "    " << group.first << LEFT_GROUP_TOKEN << '\n';
                for (const auto& tag : group.second){
                    xdl_archive << "    " << "    " << LEFT_KEY_TOKEN << tag.first << ASSEMBLER_TOKEN << tag.second << RIGHT_KEY_TOKEN << '\n';
                }
                xdl_archive << "    " << RIGHT_GROUP_TOKEN << '\n';
            }
            xdl_archive << RIGHT_INDEX_TOKEN << '\n';
        }

        //fecha o arquivo
        xdl_archive.close();

        //mostra que foi concluído com sucesso
        std::cout << "content writen in: " << xdl_file_path << '\n'; 
    }

    void xdl_map_printer(xdl_data_map _in_map){
        for(const auto& index : _in_map){
            std::cout << "Index: " << index.first << '\n';
            for (const auto& group : index.second){
                std::cout << "    " << "Group: " << group.first << '\n';
                for (const auto& tag : group.second){
                    std::cout << "    " << "    " << "Key: " << tag.first << " | " << "Value: " << tag.second << '\n';
                }
            }
        }
    }

} //namespace end