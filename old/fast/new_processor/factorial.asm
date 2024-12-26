
; Factorial

mov R2, 9

; ------------------ <- R2

mov R1, 1

:label


mul R0, R0, R2
sub R2, R2, 1 

cmp R2, 0
jg label

; ------------------ -> R0

print R0
