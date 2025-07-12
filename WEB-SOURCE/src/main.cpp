#include <filesystem>
#include <iostream>
#include <crow.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>

//incializa o crow app
crow::SimpleApp app;

//função de reconhecimento do MIME type de um arquivo
std::string get_mime_type(const std::string& extension){
    //define o tipo MIME do arquivo
    std::string mime;

    //verifica a extensão do arquivo e define o tipo MIME correspondente
    static const std::unordered_map<std::string, std::string> mime_map = {
        {".png", "image/png"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".gif", "image/gif"},
        {".bmp", "image/bmp"},
        {".webp", "image/webp"},
        {".svg", "image/svg+xml"},
        {".mp4", "video/mp4"},
        {".webm", "video/webm"},
        {".ogg", "video/ogg"},
        {".mov", "video/quicktime"},
        {".avi", "video/x-msvideo"},
        {".mp3", "audio/mpeg"},
        {".wav", "audio/wav"},
        {".flac", "audio/flac"},
        {".m4a", "audio/mp4"},
        {".aac", "audio/aac"},
        {".oga", "audio/ogg"},
        {".html", "text/html"},
        {".htm", "text/html"},
        {".css", "text/css"},
        {".js", "text/javascript"},
        {".ts", "text/typescript"},
        {".json", "application/json"},
        {".xml", "application/xml"},
        {".csv", "text/csv"},
        {".txt", "text/plain"},
        {".md", "text/markdown"},
        {".ttf", "font/ttf"},
        {".otf", "font/otf"},
        {".woff", "font/woff"},
        {".woff2", "font/woff2"},
        {".pdf", "application/pdf"},
        {".zip", "application/zip"},
        {".tar", "application/x-tar"},
        {".gz", "application/gzip"},
        {".rar", "application/vnd.rar"},
        {".7z", "application/x-7z-compressed"},
        {".exe", "application/vnd.microsoft.portable-executable"},
        {".apk", "application/vnd.android.package-archive"},
        {".ico", "image/x-icon"}
    };

    //verifica se a extensão do arquivo está no mapa de tipos MIME
    auto iterator = mime_map.find(extension);
    if (iterator != mime_map.end()){
        return iterator->second;
    }else{
        std::cerr << "[WEB-SERVER ERROR!] Unknown MIME type for extension \"" << extension << "\"!\n";
        return "application/octet-stream";
    }
}

//página de erro 404 Not Found
crow::response not_found(const crow::request& req){
    //resposta para requisição não encontrada
    crow::response res;
    //resposta para a requisição não encontrada
    std::cerr << "[WEB-SERVER NOT FOUND ERROR!] Route '" << req.url << "' not found!\n";
    std::cerr << "[WEB-SERVER RETURN] 404 Not Found" << '\n';

    //define o código de status da resposta como 404
    res.code = 404;
    //define o corpo da resposta como uma página HTML de erro 404
    res.body = R"(
        <!DOCTYPE html>
        <html lang="pt-br">
        <head>
            <meta charset="UTF-8">
            <title>404 Not Found</title>
            <link rel="shortcut icon" href="/favicons/yellow_alert_favicon.ico">
        </head>
        <body>
            <h1>404 Not Found</h1>
            <p>A página '<code>)" + req.url + R"(</code>' não foi encontrada!</p>
        </body>
        </html>
    )";

    return res;
}

//página 500 Internal Server Error
crow::response internal_server_error(const crow::request& req){
    //resposta para requisição não encontrada
    crow::response res;
    //resposta para a requisição não encontrada
    std::cerr << "[WEB-SERVER INTERNAL ERROR!] Something went wrong! '" << req.url << "'!\n";
    std::cerr << "[WEB-SERVER RETURN] 500 Internal Server Error" << '\n';

    //define o código de status da resposta como 404
    res.code = 500;
    //define o corpo da resposta como uma página HTML de erro 404
    res.body = R"(
        <!DOCTYPE html>
        <html lang="pt-br">
        <head>
            <meta charset="UTF-8">
            <title>500 Internal Server Error</title>
            <link rel="shortcut icon" href="/favicons/redx_favicon.ico">
        </head>
        <body>
            <h1>500 Internal Server Error</h1>
            <p>A página '<code>)" + req.url + R"(</code>' ocasionou um erro interno no servidor!</p>
        </body>
        </html>
    )";

    return res;


}

//função de chamada de favicons
crow::response favicon(std::string filename){
    //resposta para a requisição de favicon
    crow::response res;
    //buffer de favicon
    std::stringstream favicon_buffer;
    //abre o arquivo de imagem da requisição do favicon
    std::ifstream file("static/favicons/" + filename, std::ios::binary);

    //verifica se o favicon foi aberto corretamente
    if(file.is_open()){
        //lê e armazena o favicon no buffer
        favicon_buffer << file.rdbuf();

        //fecha o arquivo
        file.close();
    }else{
        //se não puder abrir o arquivo, fecha o arquivo e retorna um erro e a página 404
        file.close();
        std::cerr << "[WEB-SERVER ERROR!] Favicon '" << filename << "' not found!\n";
        std::cerr << "[WEB-SERVER RETURN] 404 Not Found" << '\n';
        return crow::response(404, "<h1>404 Not Found</h1>");
    }

    //define o cabeçalho da resposta com o tipo MIME do favicon
    res.set_header("Content-Type", "image/x-icon");

    //cria a resposta com o buffer de imagem
    res.body = favicon_buffer.str();

    //define o código de status da resposta como 200
    res.code = 200;

    //retorna a resposta com o favicon
    return res;
}

//função de chamada de imagens
crow::response image(std::string filename){
    //resposta para a requisição de imagem
    crow::response res;
    //buffer de imagem
    std::stringstream image_buffer;
    //abre o arquivo de imagem da requisição
    std::ifstream file("static/images/" + filename, std::ios::binary);
    //variável do tipo mime
    std::string mime;

    //carrega o caminho do arquivo e a extensão para verificação do tipo MIME
    std::filesystem::path path("static/images/" + filename);

    //verifica se a imagem foi aberta corretamente
    if(file.is_open()){
        //lê e armazena a imagem no buffer
        image_buffer << file.rdbuf();

        //fecha o arquivo
        file.close();
    }else{
        //se não puder abrir o arquivo, fecha o arquivo e retorna um erro e a página 404
        file.close();
        std::cerr << "[WEB-SERVER ERROR!] Image '" << filename << "' not found!\n";
        std::cerr << "[WEB-SERVER RETURN] 404 Not Found" << '\n';
        return crow::response(404, "<h1>404 Not Found</h1>");
    }

    //define o tipo MIME da imagem usando a extensão do arquivo
    mime = get_mime_type(path.extension().string());

    //define o cabeçalho da resposta com o tipo MIME da imagem
    res.set_header("Content-Type", mime);

    //cria a resposta com o buffer de imagem
    res.body = image_buffer.str();

    //define o código de status da resposta como 200
    res.code = 200;

    //retorna a resposta com a imagem e o MIME type
    return res;
}

//função de leitura do arquivo index.html
std::string read_index(){
    //abrir o arquivo index.html
    std::ifstream file("index.html");
    //buffer de arquivo HTML
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
        std::cerr << "[WEB-SERVER RETURN] 404 Not Found" << '\n';
        return "<h1>404 Not Found</h1>";
    }
}

//função para parar o servidor remotamente
crow::response server_stop(){
    //função para parar o servidor
    std::cout << "[WEB-SERVER COMMAND] stopping crow...\n";
    app.stop();
    std::cout << "[WEB-SERVER COMMAND] crow is stopped!\n";
    return crow::response(200, "<h1>Crow server stopped!</h1>");
}

int main(int argc, char* argv[]){
    //define a rota principal
    CROW_ROUTE(app, "/")(read_index);

    //define a rota para imagens
    CROW_ROUTE(app, "/images/<string>")(image);

    //define rota para favicons
    CROW_ROUTE(app, "/favicons/<string>")(favicon);

    //define a rota para o encerramento do servidor
    CROW_ROUTE(app, "/stop")(server_stop);

    //define a rota para 404 Not Found
    CROW_CATCHALL_ROUTE(app)(not_found);

    //define a porta do servidor
    app.port(8080)
        .run();

    
    return 0;
}
