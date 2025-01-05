


; FASM ASSEMBLER FILE
format MS64 COFF
use64

; ----------------------------------------------
; File:     read_write_fs.asm
; Brief:    Stack. FS register access.
; Version:  V0.0.1
; Date:     4. Jan 2025
; Author:   Matvey Rybalkin
; ----------------------------------------------

section '.text' code readable executable

; Callable as Microsoft x64
public read_fs
public write_fs

; -------------------------------------
;  size_t utf8_len(const utf8_string_t str)
; -------------------------------------
read_fs:
    ret

write_fs:
    ret


