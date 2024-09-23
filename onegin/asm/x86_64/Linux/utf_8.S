

; FASM ASSEMBLER FILE
format COFF
use64

; ----------------------------------------------
; File:     x86_64/Linux/utf_8.S
; Brief:    Onegin App. UTF-8 strings functions.
; Version:  V0.0.1
; Date:     19. Sep 2024
; Author:   Matvey Rybalkin
; ----------------------------------------------

section '.text' code readable executable

; Callable as System V
public utf8_len

; -------------------------------------
;  size_t utf8_len(const utf8_string_t str)
; -------------------------------------
utf8_len:
    ; char* ptr = str;
    mov rsi, rdi
    ; size_t len = 0;
    xor rdx, rdx
next_char:
    ; while ((*ptr) == '\0')
    lodsb
    test al, al
    ; goto done
    jz done

    and al, 0C0h
    cmp al, 80h
    je next_char

    ; len++;
    inc rdx
    jmp next_char
done:
    ; return len;
    mov rax, rdx
    ret
    

