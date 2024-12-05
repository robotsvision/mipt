
; Fibonachi

mov R2, 10 ; n

; ------------------ <- R2

cmp R2, 2
jl end

mov R3, R2
sub R3, R3, 1

mov R4, R2
sub R4, R4, 2

; ???

; ------------------ -> R0

:end

