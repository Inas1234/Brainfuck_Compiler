#include <iostream>
#include "Mlib.h"
#include "./src/Tokenizer.hpp"
#include "./src/Parser.hpp"
#include "./src/Generator.hpp"

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

    Generator generator(bytecode);
    generator.generate();
    generator.writeToFile("out.asm");    

    system("nasm -felf64 out.asm -o out.o");
    system("ld out.o -o out");
    return 0;
}