#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "xdl.hpp"

file_reader::file_reader(std::string path){
    xdl_file_path = path;
}

node file_reader::parse(){
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

            //teste de reconehciemnto de grupos
            std::cout << _variable_group_name << '\n';



        }
        
        //verifica se é uma tag
        if(rawdata.find('[')!=std::string::npos && rawdata.find(':')!=std::string::npos && rawdata.find(']')!=std::string::npos){
            //localiza e armazena a posição da primeira aparição do LEFT_KEY_TOKEN [
            int _tag_name_left_pos = rawdata.find_first_of(LEFT_KEY_TOKEN); //armazena na variável de posição de inicialização de uma tag

            //localiza e armazena a posição da primeira aparição do LEFT_KEY_TOKEN [
            int _tag_name_right_pos = rawdata.find_first_of(RIGHT_KEY_TOKEN); //armazena na variável de posição de inicialização de uma tag
            
        }



        //verifica se grupos estão fechados
        if(rawdata.find('}')!=std::string::npos){
            group_lock++;
        }

        //aumenta o indicador de linhas
        current_line++;
    }

    //se encontrar um grupo aberto a partir da variável group_lock o parseamento é parado
    if(group_lock<0){
        xdl_archive.close(); //<--fecha o arquivo e libera o stream de texto do arquivo da memória
        std::cerr << "XDL operation with file->" << xdl_file_path << " stoped by error in file, has many open groups" << '\n';
    }

    //retorno padrão de teste
    node oi={"oi", "oi"};
    return oi;

    /*===================================*/


}