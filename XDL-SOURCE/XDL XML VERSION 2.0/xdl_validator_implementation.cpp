#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "xdl.hpp"


namespace xdl{
    bool check_ident_errors(const std::string& xdl_file_path){
        //inicialização de stream
        std::ifstream raw_input_data(xdl_file_path);

        //Verifica se o arquivo foi aberto corretamente
        if(!raw_input_data.is_open()){
            std::cerr << "[XDL VALIDATOR - IDENTATION] Failed to open XDL archive in validating mode!" << '\n';
            //Se não puder abrir o arquivo, fecha o arquiv, gera um erro e retorna false
            raw_input_data.close();
            std::cerr << "[XDL VALIDATOR- IDENTATION] XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
            return false;
        }

        //objeto de armazenagem de texto lido na linha atual dentro do arquivo
        std::string text;
        
        //objeto de armazenagem da linha atual
        int current_line = 1;

        //analisador de linhas carregadas dentro da string text
        while(std::getline(raw_input_data, text)){
            //verifica se existe identação
            if(text.find_first_of(' ') >= 0){
                //posição do último caractere de identação
                int ident_right_position = text.find_first_not_of(' ');
                
                //verifica se a identação é um múltiplo do número quatro (4) ou se é uma string vazia
                if(ident_right_position % 4 == 0){
                    //aviso de êxito na verificação do verificador de identação
                    std::cout << "[XDL VALIDATOR - IDENTATION] LINE: " << current_line << " VALIDATED!" << '\n';
                }else if(text.empty()){
                    //aviso de êxito na verificação do verificador de identação
                    std::cout << "[XDL VALIDATOR - IDENTATION] LINE: " << current_line << " VALIDATED!" << '\n';
                }else{
                    //aviso de erro na verificação do verificador de identação
                    std::cerr << "[XDL VALIDATOR - IDENTATION] LINE: " << current_line << " there's an identation error!" << '\n';
                    return false;
                }
            }

            //aumenta o indicador d alinha atual
            current_line++;

        }

        //retorno padrão
        return false;
    }




    bool check_spacement_errors(const std::string& xdl_file_path){
        return false;
    }




    bool check_tag_syntax_errors(const std::string& xdl_file_path){
        //inicialização de stream
        std::ifstream raw_input_data(xdl_file_path);

        //Verifica se o arquivo foi aberto corretamente
        if(!raw_input_data.is_open()){
            std::cerr << "[XDL VALIDATOR - TAG SYNTAX] Failed to open XDL archive in validating mode!" << '\n';
            //Se não puder abrir o arquivo, fecha o arquiv, gera um erro e retorna false
            raw_input_data.close();
            std::cerr << "[XDL VALIDATOR - TAG SYNTAX] XDL operation with file->" << xdl_file_path << " stoped!" << '\n';
            return false;
        }

        //objeto de armazenagem de texto lido na linha atual dentro do arquivo
        std::string text;

        //objeto de armazenagem da linha atual
        int current_line = 1;

        //analisador de linhas carregadas dentro da string text
        while(std::getline(raw_input_data, text)){
            //buffers de contagem
            int left_count_buffer = 0;
            int right_count_buffer = 0;

            //contador de caractéres de tags existentes
            for(char current_char : text){
                //incrementadores de buffers de contagem
                if(current_char == '<'){
                    //se o caractére atual retornado pelo operador ternário for < incremente o left_count_buffer
                    left_count_buffer++;
                    std::cout << "[XDL VALIDATOR - LEFT TAG SYNTAX] left char '<' found in line: " << current_line<< '\n';
                }else if(current_char == '>'){
                    //se o caractére atual retornado pelo operador ternário for > incremente o right_count_buffer
                    right_count_buffer++;
                    std::cout << "[XDL VALIDATOR - RIGHT TAG SYNTAX] right '>' char found in line: " << current_line<< '\n';
                }
            }
            //fim da bufferização de caractéres

            //contagem e verificação de quantidade de caractéres < e >
            //se houver o caractere < e > 
            if(text.find_first_of('>') != std::string::npos && text.find_last_of('<') != std::string::npos && text.find('/')){
                //se tiver mais de um caractére de fechamento esquerdo e direito efetue a verificação
                if(left_count_buffer > 1 && right_count_buffer > 1){
                    //se haver 2 caractéres de fechamento esquerdo
                    if(left_count_buffer == 2){
                        std::cout << "[XDL VALIDATOR - LEFT TAG SYNTAX] LINE: " << current_line << " VALIDATED!" << '\n';
                    }else{
                        std::cerr << "[XDL VALIDATOR - LEFT TAG SYNTAX] LINE: " << current_line << " there's an additional or missing '<' causing an error!" << '\n';
                        return false;
                    }

                    //se haver 2 caractéres de fechamneto direito
                    if(right_count_buffer == 2){
                        std::cout << "[XDL VALIDATOR - RIGHT TAG SYNTAX] LINE: " << current_line << " VALIDATED!" << '\n';
                    }else{
                        std::cerr << "[XDL VALIDATOR - RIGHT TAG SYNTAX] LINE: " << current_line << " there's an additional or missing '>' causing an error!" << '\n';
                        return false;
                    }

                    //se a divisão dos buffers for diferente de 1 reotrne falso
                    if(left_count_buffer / right_count_buffer != 1){
                        std::cerr << "[XDL VALIDATOR - TAG SYNTAX] LINE: " << current_line << " there's an additional or missing charactere '<' or '>'!" << '\n';
                        return false;
                    }

                }
            }else if(text.empty()){
                std::cout << "[XDL VALIDATOR - TAG SYNTAX] EMPTY LINE: " << current_line << " VALIDATED!" << '\n';
            }else{
                std::cerr << "[XDL VALIDATOR - TAG SYNTAX] LINE: " << current_line << " there's an additional or missing '/' causing an error or the tag had an fatal error!" << '\n';
                return false;
            }

            //identifica a posição da primeira tag, a tag de abertura
            int first_left_tag_pos = text.find_first_of('<'); //tag padrão junto com a tag de declaração de tag comum
            int first_right_tag_pos = text.find_first_of('>'); //tag padrão junto com a tag declaração de tag comum

            //identifica a posição da segunda tag, a tag de fechamento
            int last_left_tag_pos = text.find_last_of('/');
            int last_right_tag_pos = text.find_last_of('>');

            //buffer de tag
            static std::string first_tag="";
            static std::string second_tag="";

            //atribuíção de tags para teste de fechamento

            //verifica se é uma tag junto com um valor ou uma tag de abertura de grupo
            if(left_count_buffer == 2 && right_count_buffer == 2){
                //armazena o conteúdo da tag de abertura na sub-string na variável first_tag_to_check
                std::string first_tag_to_check = text.substr(first_left_tag_pos + 1, first_right_tag_pos - first_left_tag_pos - 1);
                first_tag = first_tag_to_check;
                
                //armazena o conteúdo da tag de fechamento na sub-string na variável second_tag_to_check
                std::string second_tag_to_check = text.substr(last_left_tag_pos + 1, last_right_tag_pos - last_left_tag_pos - 1);
                second_tag = second_tag_to_check;
            }

            //verifica se as tags são iguais para efetuar o fechamento
            if(first_tag != second_tag){
                std::cerr << "[XDL VALIDATOR - TAG SYNTAX] LINE: " << current_line << " current object: " << first_tag << " open-tag different from close-tag, there's a tag closing error!" << '\n';
                return false;
            }

            //aumenta o contador de linhas
            current_line++;
        }

        return false;
    }



    bool check_group_syntax_errors(const std::string& xdl_file_path){
        return false;
    }



    bool check_predefined_value_errors(const std::ifstream& raw_input_data){
        return false;
    }



    bool check_close_errors(const std::ifstream& raw_input_data){
        return false;
    }

}