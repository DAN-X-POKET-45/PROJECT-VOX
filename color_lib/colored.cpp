#include <iostream>
#include <string>

/*
ESC Code Sequence   | Description
\033[38;5;{ID}m	Set | foreground color. {ID 0-256}
\033[48;5;{ID}m	Set | background color. {ID 0-256}
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

std::string foreground_color(int ANSI_ID) {
    if (ANSI_ID > 255 || ANSI_ID < 0) {
        std::cerr << "ANSI_ID INVALID " << ANSI_ID << " (Should be between 0 and 255)" << '\n';
        return "";
    }

    return "\033[38;5;" + std::to_string(ANSI_ID) + "m";
}

std::string background_color(int ANSI_ID) {
    if (ANSI_ID > 255 || ANSI_ID < 0) {
        std::cerr << "ANSI_ID INVALID " << ANSI_ID << " (Should be between 0 and 255)" << '\n';
        return "";
    }

    return "\033[48;5;" + std::to_string(ANSI_ID) + "m";
}

void list_ANSI_table_colors(){
    // Exibindo todas as 256 cores
    for (int i = 0; i < 256; ++i) {
        std::cout << "\033[38;5;" << i << "m" << "Cor " << i << ANSI_RESET << " ";
        if (i % 16 == 15) std::cout << std::endl;
    }
}

int main() {
    std::cout << ANSI_BOLD << RED << "Texto em negrito e vermelho" << ANSI_RESET << std::endl;
    std::cout << ANSI_ITALIC << GREEN << "Texto em itálico e verde" << ANSI_RESET << std::endl;
    std::cout << ANSI_UNDERLINE << BLUE << "Texto sublinhado e azul" << ANSI_RESET << std::endl;
    std::cout << ANSI_CROSSED_OUT << YELLOW << "Texto tachado e amarelo" << ANSI_RESET << std::endl;
    std::cout << BRIGHT_MAGENTA << "Texto magenta brilhante" << ANSI_RESET << std::endl;

    std::cout << foreground_color(1) << "texto vermelho" << '\n';
    std::cout << background_color(0) << "fundo  preto" << '\n';

    return 0;
}
