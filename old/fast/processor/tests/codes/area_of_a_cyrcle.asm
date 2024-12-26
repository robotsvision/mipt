
; Area of a cyrcle application: R0 = Pi, R1 = r
mov R0, 3
mov R1, 2

mul R1, R1, R1
mul R2, R1, R0


out "A = "
out R2


; All instructions

out

hlt
mov
add
sub
div
mul

cmp
jmp
je
jne
jg
jl
jge
jle


call
ret

