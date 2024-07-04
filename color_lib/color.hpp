#include <iostream>
#include <string>

/*
ESC Code Sequence   | Description
\033[38;5;{ID}m	Set | foreground color. {ID-256}
\033[48;5;{ID}m	Set | background color.
*/

// Definindo as sequências de escape ANSI para formatação de texto
#define ANSI_RESET          "\033[0m"
#define ANSI_BOLD           "\033[1m"
#define ANSI_FAINT          "\033[2m"      // Fraco (não amplamente suportado)
#define ANSI_ITALIC         "\033[3m"
#define ANSI_UNDERLINE      "\033[4m"
#define ANSI_BLINK          "\033[5m"      // Piscar (não amplamente suportado)
#define ANSI_REVERSE        "\033[7m"
#define ANSI_CONCEAL        "\033[8m"      // Ocultar (não amplamente suportado)
#define ANSI_CROSSED_OUT    "\033[9m"

#define ANSI_BOLD_OFF       "\033[22m"
#define ANSI_ITALIC_OFF     "\033[23m"
#define ANSI_UNDERLINE_OFF  "\033[24m"
#define ANSI_BLINK_OFF      "\033[25m"
#define ANSI_REVERSE_OFF    "\033[27m"
#define ANSI_CONCEAL_OFF    "\033[28m"

// Definindo as cores padrão
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Definindo as cores brilhantes
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

// Definindo as cores de fundo padrão
#define BACKGROUND_BLACK   "\033[40m"
#define BACKGROUND_RED     "\033[41m"
#define BACKGROUND_GREEN   "\033[42m"
#define BACKGROUND_YELLOW  "\033[43m"
#define BACKGROUND_BLUE    "\033[44m"
#define BACKGROUND_MAGENTA "\033[45m"
#define BACKGROUND_CYAN    "\033[46m"
#define BACKGROUND_WHITE   "\033[47m"

// Definindo as cores de fundo brilhantes
#define BACKGROUND_BRIGHT_BLACK   "\033[100m"
#define BACKGROUND_BRIGHT_RED     "\033[101m"
#define BACKGROUND_BRIGHT_GREEN   "\033[102m"
#define BACKGROUND_BRIGHT_YELLOW  "\033[103m"
#define BACKGROUND_BRIGHT_BLUE    "\033[104m"
#define BACKGROUND_BRIGHT_MAGENTA "\033[105m"
#define BACKGROUND_BRIGHT_CYAN    "\033[106m"
#define BACKGROUND_BRIGHT_WHITE   "\033[107m"

// Definindo todas as 256 cores ANSI
#define COLOR0   "\033[38;5;0m"
#define COLOR1   "\033[38;5;1m"
#define COLOR2   "\033[38;5;2m"
#define COLOR3   "\033[38;5;3m"
#define COLOR4   "\033[38;5;4m"
#define COLOR5   "\033[38;5;5m"
#define COLOR6   "\033[38;5;6m"
#define COLOR7   "\033[38;5;7m"
#define COLOR8   "\033[38;5;8m"
#define COLOR9   "\033[38;5;9m"
// ...
// Continuar para todas as 256 cores
#define COLOR255 "\033[38;5;255m"

std::string foreground_color(int ANSI_ID){
    if(ANSI_ID > 255 || ANSI_ID < 0){
        std::cerr << "ANSI_ID INVALID " << ANSI_ID << " (Should be between 0 and 255)" << '\n';
        return "";
    }

    std::string code = "\033[38;5;" + std::to_string(ANSI_ID) + "m";
    return code;
}

std::string background_color(int ANSI_ID){
    if(ANSI_ID > 255 || ANSI_ID < 0){
        std::cerr << "ANSI_ID INVALID " << ANSI_ID << " (Should be between 0 and 255)" << '\n';
        return "";
    }

    std::string code = "\033[48;5;" + std::to_string(ANSI_ID) + "m";
    return code;
}
