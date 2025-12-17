#include <iostream>

// g++ -std=c++17 -DENABLE_GNU_RANGE 03.cpp

static const char* classifyAsciiChar(char ch) {
    switch (ch) {
#if defined(__GNUG__) && defined(ENABLE_GNU_RANGE)
        case 'A' ... 'Z': return "заглавные буквы";
        case 'a' ... 'z': return "строчные буквы";
        case '0' ... '9': return "десятичные цифры";
#else
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
        case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
        case 'V': case 'W': case 'X': case 'Y': case 'Z':
            return "заглавные буквы";

        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
        case 'v': case 'w': case 'x': case 'y': case 'z':
            return "строчные буквы";

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return "десятичные цифры";
#endif

        case '!': case '"': case '#': case '$': case '%': case '&': case '\'':
        case '(': case ')': case '*': case '+': case ',': case '-': case '.':
        case '/': case ':': case ';': case '<': case '=': case '>': case '?':
        case '@': case '[': case '\\': case ']': case '^': case '_': case '`':
        case '{': case '|': case '}': case '~':
            return "знаки препинания";

        default:
            return "прочие символы";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char inputCharacter;
    while (std::cin.get(inputCharacter)) {
        unsigned char code = static_cast<unsigned char>(inputCharacter);
        if (code < 32 || code > 127) {
            continue;
        }
        std::cout << classifyAsciiChar(inputCharacter) << '\n';
    }
    return 0;
}


