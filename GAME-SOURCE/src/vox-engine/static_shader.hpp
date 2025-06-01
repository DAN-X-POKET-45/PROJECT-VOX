class static_shader{
public:

    //identificador do shader
    unsigned int ID;

    //construtor que vai carregar a fonte do shader, compilar, testar erros e linkar ao programa de shader
    static_shader();

    //vertex shader
    const char* vertex_shader = "";

    //fragment shader
    const char* fragment_shader = "";



    //compilar os shaders de vértice e fragmento
    void compile_shaders(const char* vertex_shader, const char* fragment_shader);

    //testa erros de compilação
    void test_compile_errors();

    //destrutor
    ~static_shader();

private:
    //linkador de shader ao programa
    void link_shader();




}