.data
	inicio:   	.byte 0  
	fin: 		.byte 10  	; Suma resultante = 9+10+11+12+13+14+15+16 = 100 
	res:         .byte 0     ; Espacio reservado para “res” de 2 bytes.
       cero:        .byte 0     ;  Un cero lógico

.text
	la $2, inicio  ; Carga la dirección de memoria de la variable “inicio”.
	la $3, fin     ; Carga la dirección de memoria de la variable “fin”.
	la $4, res     ; Carga la dirección de “res” (donde se almacenará el resultado).
       la $5, cero    ; Carga la dirección de memoria de la variable “cero".

       lb $6, 0($2); Carga sin desplazamiento de $2, es decir: inicio
       lb $7, 0($3); Carga sin desplazamiento de $3, es decir: fin
       lb $8, 0($4); Carga sin desplazamiento de $4, es decir: res
       lw $9, 0($5); Carga sin desplazamiento de $5, es decir: cero
       
bucle: bgt $7, $6, final; Si fin > inicio, entonces salta a fin, de lo contrario entra a bucle
       
       add $9, $9, $6; Suma $9 (sum) a $6 (i = inicio) y lo carga en $9
       addi $6, $6, 1; Suma inmediata de $6 (i = inicio) más 1, lo carga en $6
       
       j bucle; Salto incondicional a bucle
       
final: sw $8, 0($9); Store del resultado ($9 = sum) en $8 (res)

;///////////////////////////////////////////////////////////////////////////////////////////////////////////

.data
    inicio: .byte 0
    fin:    .byte 10
    res:    .space 2

.text
    la $2, inicio
    la $3, fin
    la $4, res

    lb $5, 0 ($2)
    lb $6, 0 ($3)

while: 
    sgt $9, $5, $6
    bgtz $9, Exit
    add $7, $7, $5  ; sum = sum + i
    addi $5, $5, 1  ; i++
    j while

Exit: 
    sb $7, 0 ($4) ; TODO: ¿Qué hacemos aquí?
