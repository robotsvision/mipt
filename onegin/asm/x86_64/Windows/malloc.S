; FASM ASSEMBLER FILE
format MS64 COFF
use64

; ----------------------------------------------
; File:     x86_64/Windows/alloc.S
; Brief:    Onegin App. Memory allocation.
; Version:  V0.0.1
; Date:     19. Sep 2024
; Author:   Matvey Rybalkin
; ----------------------------------------------

section '.text' code readable executable

; Callable as Microsoft x64
public lcalloc
public lcalloc2

extrn VirtualAlloc
extrn RtlZeroMemory

; Windows Macroses

MEM_COMMIT equ 1000h
MEM_RESERVE equ 2000h
PAGE_READWRITE equ 04h

lcalloc2:
    test rcx, rcx
    jz return_NULL

    mov rdx, rcx ; size
    xor rcx, rcx ; NULL
    mov r8, (MEM_COMMIT or MEM_RESERVE)
    mov r9, (PAGE_READWRITE)
    call VirtualAlloc


.return_NULL:
    xor rax, rax
.return:
    ret

; -------------------------------------
;  void* lcalloc(size_t num_of_elements, size_t size_of_element)
; -------------------------------------
lcalloc:
    ; if (num_of_elements == 0) { return mem; }
    test rcx, rcx
    jz return_NULL
    test rdx, rdx
    jz return_NULL

    ; size_of_element
    mov rax, rdx

    ; size = num_of_elements * size_of_element
    mul rcx
    
    ; if (rdx != 0) -> overflow
    test rax, rax
    ; return NULL
    jnz return_NULL

    ; size ->
    push rax

    ; ptr =  VirtualAlloc(size ...) 
    xor rcx, rcx ; NULL
    mov rdx, rax ; size
    mov r8, (MEM_COMMIT or MEM_RESERVE)
    mov r9, (PAGE_READWRITE)
    call VirtualAlloc

    ; if (ptr == NULL) { return NULL }
    test rax, rax
    jz return
    
    ; ZeroMemory(ptr, size)
    mov rcx, rax
    ; <- size
    pop rdx
    mov rbx, [RtlZeroMemory]
    call rbx

return_NULL:
    xor rax, rax
return:
    ret
