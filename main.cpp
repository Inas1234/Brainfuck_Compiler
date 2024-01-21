#include <iostream>
#include "Mlib.h"
#include "./src/Tokenizer.hpp"
#include "./src/Parser.hpp"

int main(int argc, char** argv){
    if (argc <= 1){
        std::cerr << "Usage: <main> <.bf>" << std::endl;
        return 1;
    }

    std::string content = mlib_read_file(argv[1]);

    Tokenizer tokenizer(content);
    std::vector<Token> tokens = tokenizer.tokenize();
    Parser parser(tokens);
    std::vector<Bytecode> bytecode = parser.parse();
    return 0;
}