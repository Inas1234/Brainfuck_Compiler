section .bss
    memory: resb 30000
section .text
    global _start
_start:
    mov rbx, memory
    sub byte [rbx], 4
label0:
    cmp byte [rbx], 0
    je endlabel0
    sub byte [rbx], 4
    add rbx, 1
    add byte [rbx], 1
    sub rbx, 1
    cmp byte [rbx], 0
    jne label0
endlabel0:
    add rbx, 1
    add byte [rbx], 2
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
label1:
    cmp byte [rbx], 0
    je endlabel1
    sub byte [rbx], 3
    add rbx, 1
    add byte [rbx], 1
    sub rbx, 1
    cmp byte [rbx], 0
    jne label1
endlabel1:
    add rbx, 1
    add byte [rbx], 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add byte [rbx], 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    sub byte [rbx], 4
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add byte [rbx], 9
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
label2:
    cmp byte [rbx], 0
    je endlabel2
    sub byte [rbx], 2
    add rbx, 1
    add byte [rbx], 5
    sub rbx, 1
    cmp byte [rbx], 0
    jne label2
endlabel2:
    add rbx, 1
    add byte [rbx], 3
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
label3:
    cmp byte [rbx], 0
    je endlabel3
    sub byte [rbx], 2
    add rbx, 1
    add byte [rbx], 5
    sub rbx, 1
    cmp byte [rbx], 0
    jne label3
endlabel3:
    add rbx, 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add rbx, 1
    sub byte [rbx], 2
label4:
    cmp byte [rbx], 0
    je endlabel4
    sub byte [rbx], 5
    add rbx, 1
    add byte [rbx], 1
    sub rbx, 1
    cmp byte [rbx], 0
    jne label4
endlabel4:
    add rbx, 1
    sub byte [rbx], 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    sub byte [rbx], 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add byte [rbx], 1
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add byte [rbx], 13
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    add rbx, 1
    add byte [rbx], 10
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall
    mov rax, 60
    xor rdi, rdi
    syscall
