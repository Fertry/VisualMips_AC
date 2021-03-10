; Implementar el siguiente código C en MIPS
;       …
;      sum = 0;
;        i = inicio;
;        f = fin;
;        while(i<=f)
;        {
;       sum = sum + i;
;        i++;
;        }
;        res = sum;
;        …

.data
	inicio:   	.byte 9      ; i = inicio, con valor 9
	fin: 		.byte 16     ; f = fin, con valor 16
	res:         .space 2     ; Espacio reservado para “res” de 2 bytes

.text
	la $2, inicio            ; Carga la dirección de memoria de la variable “inicio”
	la $3, fin               ; Carga la dirección de memoria de la variable “fin”
	la $4, res               ; Carga la dirección de “res” (donde se almacenará el resultado)

       lb $5, 0($2)            ; Carga sin desplazamiento de $2,esto es, $5 es inicio = i
       lb $6, 0($3)            ; Carga sin desplazamiento de $3,esto es, $6 es fin = f
       
bucle: slt $7, $6, $5          ; Si fin ($6) > inicio ($5), entonces carga un 1 en $7, de lo contrario, un 0
       
       bne $7, $0, final      ; Si en $7 se cargó un 0 (fin < inicio), saltamos a final, de lo contrario continua
       
       add $8, $7, $5         ; Sumamos y guardamos en $8. En $7 ya hay un cero si acabamos de entrar por primera vez, $7 sería sum
       addi $5, $5, 1         ; Suma inmediata a $5 + 1 donde 
       
       j bucle                ; Salto incondicional a bucle
       
final: sb $4, 0($8)           ; Store del resultado ($8 = sum) en $4 (res)       