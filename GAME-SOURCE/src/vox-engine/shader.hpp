class static_shader{
public:

    //identificador do shader
    unsigned int ID;

    //construtor que vai pegar a fonte do shader, compilar, testar erros e linkar
    static_shader();

    //compilador a partir de arquivos fonte
    shader_source(std::string vertex_file_path, std::string fragment_file_Path);

    //destrutor
    ~static_shader();

private:
    //compilador de shader
    unsigned int compile_shader();

    //linkador de shader ao programa
    void link_shader();

    //testa erros de compilação
    void test_compile_errors();
}