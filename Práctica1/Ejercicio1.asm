.data
	inicio:   	.byte 9   
	fin: 		.byte 16  	; Suma resultante = 9+10+11+12+13+14+15+16 = 100 
	res:         .space 2     ; Espacio reservado para “res” de 2 bytes.

.text
	la $2, inicio  ; Carga la dirección de memoria de la variable “inicio”.
	la $3, fin     ; Carga la dirección de memoria de la variable “fin”.
	la $4, res     ; Carga la dirección de “res” (donde se almacenará el resultado).

       lb $5, 0($2); Carga sin desplazamiento de $2
       lb $6, 0($3); Carga sin desplazamiento de $3
       lb $7, 0($4); Carga sin desplazamiento de $4
       lw $8, 0($0); Carga sin desplazamiento de 0 en $8
       
bucle: bgt $6, $5, final; Si fin > inicio, entonces salta a fin, de lo contrario entra a bucle
       
       add $8, $8, $5; Suma $8 (sum) a $5 (i = inicio) y lo carga en $8
       addi $5, $5, 1; Suma inmediata de $5 (i = inicio) más 1, lo carga en $5
       
       j bucle; Salto incondicional a bucle
       
final: sw $9, 0($8); Store del resultado ($8 = sum) en $9 (res)
       