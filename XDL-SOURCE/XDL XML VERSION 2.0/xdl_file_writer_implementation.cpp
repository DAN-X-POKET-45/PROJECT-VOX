#include <initializer_list>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "xdl.hpp"



namespace xdl{
    //construtor
    file_writer::file_writer(const std::string path){
        xdl_file_path = path;
    }

    //exportador para json
    void file_writer::export_as_json(const node& content){
        //caminho para o arquivo de gravação
        xdl_archive.open(xdl_file_path);

        //Verifica se o arquivo foi aberto corretamente
        if(!xdl_archive.is_open()){
            std::cerr << "\033[31m[XDL-WRITER FILE ERROR!]\033[0m Failed to open XDL archive in write mode: " << xdl_file_path << '\n';
            //Se não puder abrir o arquivo, sai do construtor
            xdl_archive.close();
            std::cerr << "\033[31m[XDL-WRITER]\033[0m XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
        }

        //gravador de conteúdo no arquivo de destino
        json_archive_printer(content, 0);
    }

    //exportador para xdl
    void file_writer::export_as_xdl(const node& content){
        //caminho para o arquivo de gravação
        xdl_archive.open(xdl_file_path);

        //Verifica se o arquivo foi aberto corretamente
        if(!xdl_archive.is_open()){
            std::cerr << "\033[31m[XDL-WRITER FILE ERROR!]\033[0m Failed to open XDL archive in write mode: " << xdl_file_path << '\n';
            //Se não puder abrir o arquivo, sai do construtor
            xdl_archive.close();
            std::cerr << "\033[31m[XDL-WRITER]\033[0m XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
        }

        //gravador de conteúdo no arquivo de destino
        xdl_archive_printer(content, 0);
    }

    //exportador string stream
    std::stringstream& file_writer::export_as_stringstream(const node& content){
        //gravador de conteúdo na string stream
        xdl_string_stream_printer(content, 0);

        //retorno da string stream pós gravação
        return xdl_ss; 
        
    }



    //impressor recursivo para arquivo json externo
    void file_writer::json_archive_printer(const node& node_in, int ident=0){
        //variável que armazena se é ou não um grupo para a inserção de um caracteére de fechamento
        bool group = false; 

        //SE O NOME DO NODO RAÍZ NÃO FOR "root", CONTINUE A ESCRITURA (JAMAIS CRIE UM GRUPO CHAMADO ROOT)
        if(node_in.name != "root" || node_in.childs.empty()){
            //verifica se é um grupo ou uma tag:value
            if(node_in.childs.size() > 0 && node_in.value.empty() == true){
                xdl_archive << std::string(ident * 4, ' ') << '"' << node_in.name << '"' << ':' << ' ' << '{' << '\n';
                group = true;
            }else{
                xdl_archive << std::string(ident * 4, ' ') << '"' << node_in.name << '"' << ':' << node_in.value << ',' << '\n';
            }
        }else{
            ident -= 1;
        }

        //impressor recursivo de nodos dentro do vetor do nodo atual
        for(const auto& sub_nodes : node_in.childs){
            json_archive_printer(sub_nodes, ident + 1);
        }

        //se for um grupo, insere o caractére de fechamento de grupo no final da declaração do grupo
        if(group){
            xdl_archive << std::string(ident * 4, ' ') << '}' << '\n';
        }
    }

    //impressor recursivo para arquivo xdl externo
    void file_writer::xdl_archive_printer(const node& node_in, int ident=0){
        //variável que armazena se é ou não um grupo para a inserção de um caracteére de fechamento
        bool group = false; 

        //SE O NOME DO NODO RAÍZ NÃO FOR "root", CONTINUE A ESCRITURA (JAMAIS CRIE UM GRUPO CHAMADO ROOT)
        if(node_in.name != "root" || node_in.childs.empty()){
            //verifica se é um grupo ou uma tag:value
            if(node_in.childs.size() > 0 && node_in.value.empty() == true){
                xdl_archive << std::string(ident * 4, ' ') << '<' << node_in.name << '>' << '\n';
                group = true;
            }else{
                xdl_archive << std::string(ident * 4, ' ') << '<' << node_in.name << '>' << node_in.value << '<' << '/' << node_in.value << '>' << '\n';
            }
        }else{
            ident -= 1;
        }

        //impressor recursivo de nodos dentro do vetor do nodo atual
        for(const auto& sub_nodes : node_in.childs){
            xdl_archive_printer(sub_nodes, ident + 1);
        }

        //se for um grupo, insere o caractére de fechamento de grupo no final da declaração do grupo
        if(group){
            xdl_archive << std::string(ident * 4, ' ') << '<' << '/' <<node_in.name << '>' << '\n';
        }
    }

    //impressor recursivo para string stream
    void file_writer::xdl_string_stream_printer(const node& node_in, int ident=0){
        //variável que armazena se é ou não um grupo para a inserção de um caracteére de fechamento
        bool group = false; 

        //SE O NOME DO NODO RAÍZ NÃO FOR "root", CONTINUE A ESCRITURA (JAMAIS CRIE UM GRUPO CHAMADO ROOT)
        if(node_in.name != "root" || node_in.childs.empty()){
            //verifica se é um grupo ou uma tag:value
            if(node_in.childs.size() > 0 && node_in.value.empty() == true){
                xdl_ss << std::string(ident * 4, ' ') << '<' << node_in.name << '>' << '\n';
                group = true;
            }else{
                xdl_ss << std::string(ident * 4, ' ') << '<' << node_in.name << '>' << node_in.value << '<' << '/' << node_in.value << '>' << '\n';
            }
        }else{
            ident -= 1;
        }

        //impressor recursivo de nodos dentro do vetor do nodo atual
        for(const auto& sub_nodes : node_in.childs){
            xdl_string_stream_printer(sub_nodes, ident + 1);
        }

        //se for um grupo, insere o caractére de fechamento de grupo no final da declaração do grupo
        if(group){
            xdl_ss << std::string(ident * 4, ' ') << '<' << '/' <<node_in.name << '>' << '\n';
        }
    }

}