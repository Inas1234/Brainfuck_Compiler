#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>

enum class TokenType{
    INC,
    DEC,
    LEFT,
    RIGHT,
    IN,
    OUT,
    LOOP_START,
    LOOP_END
};

struct Token{
    TokenType type;
    int value;
};

class Tokenizer{
public:
    Tokenizer(const std::string& source)
        : m_source(source)
    {}

    std::vector<Token> tokenize(){
        std::vector<Token> tokens;
        while (peek().has_value())
        {
            if (peek().value() == '+'){
                size_t count = 0;
                while (peek().value() == '+' && peek().has_value()){
                    consume();
                    count++;
                }
                tokens.push_back(Token{TokenType::INC, static_cast<int>(count)});
            }
            else if (peek().value() == '-'){
                size_t count = 0;
                while (peek().value() == '-' && peek().has_value()){
                    consume();
                    count++;
                }
                tokens.push_back(Token{TokenType::DEC, static_cast<int>(count)});
            }
            else if (peek().value() == '<'){
                size_t count = 0;
                while (peek().value() == '<' && peek().has_value()){
                    consume();
                    count++;
                }
                tokens.push_back(Token{TokenType::LEFT, static_cast<int>(count)});
            }
            else if (peek().value() == '>'){
                size_t count = 0;
                while (peek().value() == '>' && peek().has_value()){
                    consume();
                    count++;
                }
                tokens.push_back(Token{TokenType::RIGHT, static_cast<int>(count)});
            }
            else if (peek().value() == ','){
                tokens.push_back(Token{TokenType::IN, 0});
                consume();
            }
            else if (peek().value() == '.'){
                tokens.push_back(Token{TokenType::OUT, 0});
                consume();
            }
            else if (peek().value() == '['){
                tokens.push_back(Token{TokenType::LOOP_START, 0});
                consume();
            }
            else if (peek().value() == ']'){
                tokens.push_back(Token{TokenType::LOOP_END, 0});
                consume();
            }
            else{
                consume();
            }
        }
        m_index = 0;
        return tokens;   
    }

private:
    std::string m_source;
    int m_index = 0;

    std::optional<char> peek(int ahead = 0){
        if (m_index + ahead >= m_source.size()){
            return {};
        }
        return m_source[m_index + ahead];
    }

    char consume(){
        return m_source[m_index++];
    }
};