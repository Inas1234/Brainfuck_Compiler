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

    void generateHeader(){
        m_output << "section .bss" << std::endl;
        m_output << "    memory: resb 30000" << std::endl;
        m_output << "section .text" << std::endl;
        m_output << "    global _start" << std::endl;
        m_output << "_start:" << std::endl;
        m_output << "    mov rbx, memory" << std::endl;
    }

    void generateFooter() {
        m_output << "    mov rax, 60\n";  
        m_output << "    xor rdi, rdi\n"; 
        m_output << "    syscall\n";
    }

    void generateByteCodeToASM(){
        std::stack<int> loopStack;
        int labelCount = 0;
        for (const auto& instruction : m_bytecode){
            switch (instruction.instruction)
            {
            case BytecodeInstruction::INC:
                m_output << "    add byte [rbx], " << instruction.argument << std::endl;
                break;
            case BytecodeInstruction::DEC:
                m_output << "    sub byte [rbx], " << instruction.argument << std::endl;
                break;
            case BytecodeInstruction::MOVE_LEFT:
                m_output << "    sub rbx, " << instruction.argument << std::endl;
                break;
            case BytecodeInstruction::MOVE_RIGHT:
                m_output << "    add rbx, " << instruction.argument << std::endl;
                break;
            case BytecodeInstruction::INPUT:
                m_output << "    mov rax, 0" << std::endl;   
                m_output << "    mov rdi, 0" << std::endl;   
                m_output << "    mov rsi, rbx" << std::endl; 
                m_output << "    mov rdx, 1" << std::endl;   
                m_output << "    syscall" << std::endl;
                break;
            case BytecodeInstruction::OUTPUT:
                m_output << "    mov rax, 1" << std::endl;   
                m_output << "    mov rdi, 1" << std::endl;   
                m_output << "    mov rsi, rbx" << std::endl; 
                m_output << "    mov rdx, 1" << std::endl;   
                m_output << "    syscall" << std::endl;
                break;
            case BytecodeInstruction::JUMP_IF_ZERO:
                 {
                    int label = labelCount++;
                    loopStack.push(label);
                    m_output << "label" << label << ":" << std::endl;
                    m_output << "    cmp byte [rbx], 0" << std::endl;
                    m_output << "    je endlabel" << label << std::endl;
                }
                break;
            case BytecodeInstruction::JUMP_IF_NOT_ZERO:
                {
                    if (loopStack.empty()) {
                        throw std::runtime_error("Unmatched loop end");
                    }
                    int label = loopStack.top();
                    loopStack.pop();
                    m_output << "    cmp byte [rbx], 0" << std::endl;
                    m_output << "    jne label" << label << std::endl; // Jump back if not zero
                    m_output << "endlabel" << label << ":" << std::endl;
                }   
                break;

            default:
                break;
            }
        }
    }

    void generate(){
        generateHeader();
        generateByteCodeToASM();
        generateFooter();        
    }

    void writeToFile(const std::string& filename){
        std::ofstream file(filename);
        file << m_output.str();
        file.close();
    }

private:
    std::vector<Bytecode> m_bytecode;
    std::stringstream m_output;
};