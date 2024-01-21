#pragma once
#include <iostream>
#include <string>  
#include <sstream>
#include <vector>
#include <optional>
#include <fstream>
#include "Parser.hpp"

class Generator{
public:
    Generator(const std::vector<Bytecode>& bytecode)
        : m_bytecode(bytecode)
    {}
private:
    std::vector<Bytecode> m_bytecode;
    std::stringstream m_output;
};