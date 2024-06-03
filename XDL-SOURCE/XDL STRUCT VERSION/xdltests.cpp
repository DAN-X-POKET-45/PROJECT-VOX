#include <iostream>
#include <string>
#include <map>

struct file{
    std::string file_name;
    std::map<std::string, file> file_content;
};

void printelement(file input, const std::string identation =""){    
    std::cout << identation << input.file_name << '\n';
    for(const auto& child : input.file_content){
        printelement(child.second, identation + "  ");
    }
}

int main(){
    file root = {
        "root", {
            {"imagens", {"imagens", {
                {"fotos_da_viagem", {"fotos_da_viagem", {
                    {"foto1.jpg", {"foto1.jpg", {}}},
                    {"foto2.jpg", {"foto2.jpg", {}}}
                }}},
                {"outras", {"outras", {
                    {"foto3.jpg", {"foto3.jpg", {}}},
                    {"foto4.jpg", {"foto4.jpg", {}}}
                }}}
            }}}
        }
    };

    printelement(root);

    return 0;
}
