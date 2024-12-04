#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "xdl.hpp"

//construtor
file_reader::file_reader(std::string path){
    xdl_file_path = path;
}

//parseador
node file_reader::parse(){
    //caminho pro arquivo
    xdl_archive.open(xdl_file_path);

    //Verifica se o arquivo foi aberto corretamente
    if(!xdl_archive.is_open()){
        std::cerr << "Failed to open XDL archive in read mode to return the data: " << xdl_file_path << '\n';
        //Se não puder abrir o arquivo, sai do construtor
        xdl_archive.close();
        std::cerr << "XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
    }



    /*===================================*/
    /*       VARIÁVEIS VARIATIVAS        */
    /*===================================*/

    //variável variativa do valor da identação
    size_t _variable_identation = 0;

    //variável variativa do nome de uma tag
    std::string _variable_tag_name="";

    //Variável variativa do valor de uma tag
    std::string _variable_tag_valor="";

    //Variável variativa do nome de um grupo de grupos ou tags e valores
    std::string _variable_group_name="";

    /*===================================*/



    /*===================================*/
    /*       TOKENS DE CARACTÉRES        */
    /*===================================*/

    //tokens de declaração de grupos
    const char LEFT_GROUP_TOKEN = '{';
    const char RIGHT_GROUP_TOKEN = '}';

    //tokens de declaração de chaves
    const char LEFT_KEY_TOKEN = '[';
    const char RIGHT_KEY_TOKEN = ']';

    //tokens de atribuição de valores
    const char VALOR_ASSEMBLER = ':';

    /*===================================*/



    /*===================================*/
    /*       VARIÁVEIS DE CHECAGEM       */
    /*===================================*/

    //variável variativa de auxílio de verificação de fechamento de grupos
    int group_lock=0;

    //declara a linha atual para o getline
    int current_line=1;

    /*===================================*/



    //declaraçao do arquivo de texto (string) bruto para o parser e o assembler
    std::string rawdata;



    /*===================================*/
    /*     LOOP PRINCIPAL DO PARSER      */
    /*===================================*/

    //analisador de linhas carregadas dentro da string rawdata
    while(std::getline(xdl_archive, rawdata)){

        //resetadores
        _variable_identation=std::string::npos;
        _variable_tag_name="";
        _variable_tag_valor="";
        _variable_group_name="";

        //identifica a identação da linha atual
        if(rawdata.find_first_not_of(' ')!=std::string::npos){
            _variable_identation = rawdata.find_first_not_of(" ");
        }

        //verifica se é um grupo
        if(rawdata.find('{')!=std::string::npos && rawdata.find(':')==std::string::npos){
            //alterna a variável group_lock para aberta
            group_lock--;

            //localiza e armazena posição da primeira aparição do LEFT_GROUP_TOKEN {
            int _group_name_right_pos = rawdata.find_first_of(LEFT_GROUP_TOKEN); //armazena na variável de posição de inicialização de um grupo 

            //lolocaliza e armazena a posição esquerda do início do nome de um grupo
            int _group_name_left_pos = rawdata.find_first_not_of(' ');

            //organizador de índices
            _variable_group_name = rawdata.substr(_group_name_left_pos, (_group_name_right_pos - _group_name_left_pos));
        }
        
        //verifica se é uma tag
        if(rawdata.find('[')!=std::string::npos && rawdata.find(':')!=std::string::npos && rawdata.find(']')!=std::string::npos){
            //localiza e armazena a posição da primeira aparição do LEFT_KEY_TOKEN [
            int _tag_name_left_pos = rawdata.find_first_of(LEFT_KEY_TOKEN); //armazena na variável de posição de inicialização de uma tag

            //localiza e armazena a posição da primeira aparição do RIGHT_KEY_TOKEN ]
            int _tag_name_right_pos = rawdata.find_first_of(RIGHT_KEY_TOKEN); //armazena na variável de posição de inicialização de uma tag

            //localiza e armazena a posição da primeira aparição do atribuidor de valor da tag :
            int _two_point_pos = rawdata.find_first_of(':'); //armazena na variável de posição de inicialização de um valor para uma tag

            //atribuidor de valor do nome da tag
            _variable_tag_name = rawdata.substr(_tag_name_left_pos + 1, (_two_point_pos - 1 - _tag_name_left_pos));

            //atribuídor de valor do valor da tag
            _variable_tag_valor = rawdata.substr(_two_point_pos + 1, (_tag_name_right_pos - _two_point_pos - 1));
        }



        //verifica se grupos de linhas anteriores são fechados na linha atual
        if(rawdata.find('}')!=std::string::npos){
            group_lock++;
        }

        //aumenta o indicador de linhas
        current_line++;

        //verifica se é uma linha vazia ou uma linha de caractére de fechamento para evitar a inserção de algo
        if(rawdata.find('}')==std::string::npos){
            //insere os dados analisados e separados dentro do main_object
            if(_variable_tag_valor.empty() && _variable_tag_name.empty()){
                node_object_assembler(_variable_group_name, "", (_variable_identation/4));
            }else if(_variable_group_name.empty()){
                node_object_assembler(_variable_tag_name, _variable_tag_valor, (_variable_identation/4));
            }
        }
    }

    //se encontrar um grupo aberto a partir da variável group_lock o parseamento é parado
    if(group_lock<0){
        xdl_archive.close(); //<--fecha o arquivo e libera o stream de texto do arquivo da memória
        std::cerr << "XDL operation with file-> " << xdl_file_path << " stoped by error in file, has many open groups" << '\n';
    }


    //ao terminar de ler todas as linhas retorna o objeto principal
    return main_object;

    /*retorno padrão de teste
    node oi={"oi", "oi"};
    return oi;*/

    /*===================================*/


}

//montador privado para cada linha do objeto node
void file_reader::node_object_assembler(const std::string& name, const std::string& valor, const int& ident){
    size_t pos = 0;
    node* current_vector = &main_object;

    //se não estiver na camada necessária (1 camada está para 4 espaços) se move até chegar na certa
    if(ident > 0){
        //enquanto a camada não for a certa, retorna o child de dentro do nó atual
        while(pos < ident){
            current_vector = &current_vector->childs.back();
            pos++;
        }

        //após chegar na camada de destino, adiciona o grupo ou tag e valor
        current_vector->add_child(name, valor);

    //se estievr sem identação, adicione na raíz
    }else if(ident == 0){
        main_object.add_child(name, valor);
    }
    

}