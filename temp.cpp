class tag{
public:
    std::map<std::string, std::string> _tag;
    std::string tag, valor;

    void append(std::string in_tag, std::string in_valor){
        _tag[in_tag]=in_valor;
        tag = in_tag;
        valor = in_valor;
    }

    int value_size(){
        return valor.size();
    }

    std::string tag_value(){
        return valor;
    }

    bool is_empty(){
        if(valor.empty()){
            return true;
        }else{return false;}
    }

    int tag_name_size(){
        return tag.size();
    }

    std::string tag_name(){
        return tag;
    }


};
