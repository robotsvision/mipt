
; Fibonachi

; a = 4, b = -2, c = 25

mov R0, 4
mov R1, -2
mov R2, 25

; ------------------ <- R0, R1, R2

; R3 = D = b^2 - 4 * a * c

push R0
push R1

mul R1, R1, R1
mul R0, R0, R2
mul R0, R0, 4
sub R3, R1, R0

cmp R3, 0
jl ERROR

; x1, x2 = -b +- sqrt(D) / 2a

pop R1
pop R0

sub R1, 0, R1
sqrt R3, R3

mul R0, R0, 2

push R3

sub R3, R1, R3
div R4, R3, R0

pop R3

add R3, R1, R3
div R5, R3, R0


:ERROR
print "Нет решений"
hlt 1

; ------------------ -> R4, R5


