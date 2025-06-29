#include <iostream>
#include <crow.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string read_index(){
    //abrir o arquivo index.html
    std::ifstream file("index.html");
    std::stringstream raw;

    //verifica se o arquivo foi aberto corretamente
    if(file.is_open()){
        //armazena todo o conteúdo do arquivo dentro do stringstream buffer
        raw << file.rdbuf();

        //fecha o arquivo
        file.close();

        //retorna o código da página HTML
        return raw.str();
    }else{
        //se não puder abrir o arquivo, fecha o arquivo e retorna um erro e a página 404
        file.close();
        std::cerr << "[WEB-SERVER ERROR!] index.html not found!" << '\n';
        std::cerr << "[WEB-SERVER RETURN] 404 Not Dound" << '\n';
        return "<h1>404 Not Found</h1>";
    }
}

int main(int argc, char* argv[]){
    //incializa o crow app
    crow::SimpleApp app;

    //define a rota principal
    CROW_ROUTE(app, "/")(read_index);

    //define a porta do servidor
    app.port(8080)
        .multithreaded()
        .run();
    return 0;
}
