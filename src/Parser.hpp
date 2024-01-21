#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <stack>
#include "Tokenizer.hpp"

enum class BytecodeInstruction {
    INC,       
    DEC,       
    MOVE_LEFT, 
    INPUT,     
    OUTPUT,    
    JUMP_IF_ZERO, 
    JUMP_IF_NOT_ZERO ,
    MOVE_RIGHT
};

struct Bytecode {
    BytecodeInstruction instruction;
    int argument; // Used for jump addresses
};


class Parser{
public:
    Parser(const std::vector<Token>& tokens)
        : m_tokens(tokens)
    {}

    std::vector<Bytecode> parse(){
        std::vector<Bytecode> bytecode;
        std::stack<size_t> loop_stack;
        for (size_t i = 0; i < m_tokens.size(); i++){
            const auto& token = m_tokens[i];
            switch (token.type){
                case TokenType::INC:
                    bytecode.push_back(Bytecode{BytecodeInstruction::INC, token.value});
                    break;
                case TokenType::DEC:
                    bytecode.push_back(Bytecode{BytecodeInstruction::DEC, token.value});
                    break;
                case TokenType::LEFT:
                    bytecode.push_back(Bytecode{BytecodeInstruction::MOVE_LEFT, token.value});
                    break;
                case TokenType::RIGHT:
                    bytecode.push_back(Bytecode{BytecodeInstruction::MOVE_RIGHT, token.value});
                    break;
                case TokenType::IN:
                    bytecode.push_back(Bytecode{BytecodeInstruction::INPUT, token.value});
                    break;
                case TokenType::OUT:
                    bytecode.push_back(Bytecode{BytecodeInstruction::OUTPUT, token.value});
                    break;
                case TokenType::LOOP_START:
                    bytecode.push_back({BytecodeInstruction::JUMP_IF_ZERO, 0});
                    loop_stack.push(bytecode.size() - 1);
                    break;
                case TokenType::LOOP_END:
                    if (loop_stack.empty()) {
                        throw std::runtime_error("Unmatched loop end");
                    }
                    {
                        size_t start = loop_stack.top();
                        loop_stack.pop();
                        bytecode.push_back({BytecodeInstruction::JUMP_IF_NOT_ZERO, static_cast<int>(start)});
                        bytecode[start].argument = bytecode.size() - 1;
                    }
                    break;
                default:
                    throw std::runtime_error("Unknown token type");
            }

            return bytecode;
        }
    }

private:
    std::vector<Token> m_tokens; 
    size_t m_index = 0;
    std::optional<Token> peek(int ahead = 0){
        if (m_index + ahead >= m_tokens.size()){
            return {};
        }
        return m_tokens[m_index + ahead];
    }

    Token consume(){
        return m_tokens[m_index++];
    }
};