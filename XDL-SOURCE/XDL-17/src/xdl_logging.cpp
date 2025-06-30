#include <initializer_list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <xdl.hpp>

namespace xdl{
    //log com impressão
    void log(log_type type, const std::string& specification, const std::string& message){
        //prefixo de especificação de mensagem de log
        std::string prefix;

        //filtragem de prefixos
        switch(type){
            case log_type::DEBUG:
                //prefixo de depuração
                prefix = "\033[1m\033[33mDEBUG\033[0m";
                break;
            case log_type::INFO:
                //prefixo de informação
                prefix = "\033[1m\033[37mINFO\033[0m";
                break;
            case log_type::WARNING:
                //prefixo de aviso
                prefix = "\033[35mWARNING\033[0m";
                break;
            case log_type::ERROR:
                //prefixo de erro
                prefix = "\033[1m\033[31mERROR\033[0m";
                break;
            case log_type::CRITICAL:
                //prefixo de erro crítico
                prefix = "\033[1m\033[31mCRITICAL\033[0m";
                break;
        }
        //se for INFO ou DEBUG, imprime no std::cout
        if(type == log_type::DEBUG || type == log_type::INFO){
            std::cout << "(" << specification << ") [" << prefix << "] " << message << '\n';
        //senão imprime no std::cerr
        }else{
            std::cerr << "(" << specification << ") [" << prefix << "] " << message << '\n';
        }
    }

    //log com retorno de std:string
    std::string log(log_type type, const std::string& specification, const std::string& message, bool return_as_str){
        //conteúdo bruto da mensagem de log
        std::stringstream log_stream;

        //prefixo de especificação de mensagem de log
        std::string prefix;

        //filtragem de prefixos
        switch(type){
            case log_type::DEBUG:
                //prefixo de depuração
                prefix = "\033[1m\033[33mDEBUG\033[0m";
                break;
            case log_type::INFO:
                //prefixo de informação
                prefix = "\033[1m\033[37mINFO\033[0m";
                break;
            case log_type::WARNING:
                //prefixo de aviso
                prefix = "\033[35mWARNING\033[0m";
                break;
            case log_type::ERROR:
                //prefixo de erro
                prefix = "\033[1m\033[31mERROR\033[0m";
                break;
            case log_type::CRITICAL:
                //prefixo de erro crítico
                prefix = "\033[1m\033[31mCRITICAL\033[0m";
                break;
        }
        //montagem da mensagem de log
        log_stream << "(" << specification << ") [" << prefix << "] " << message << '\n';

        if(return_as_str == true){
            //retorno da mensagem de log como string
            return log_stream.str();
        }else{
            //retorno da mensagem de log oculto como string
            return std::string("[...]");
        }
    }
}