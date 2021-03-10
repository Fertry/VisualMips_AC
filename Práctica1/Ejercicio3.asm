;  Implementar el siguiente código C en MIPS
;        …
;        aux = 0;
;        for(i=0; i<8; i++)
;        {
;        	aux = aux + x[i];
;       }
;        aux = aux/8;
;        res = aux;
;       …

.data
	x:      	.word 6, -4, 13, 8, -2, 11, 7, 20, 9, -3, -12, 5, 1, 23, -25, 8
	contP:		.space 4	; Debería contener el resultado final de 11
	contN:    	.space 4	; Debería contener el resultado final de 5

.text
	la $2, x        	; Dirección inicial del vector (y, por tanto, del primer elemento)
	addi $3, $0, 0	; Inicialización de registro a 0 (para contador de positivos)
	addi $4, $0, 0	; Inicialización de registro a 0 (para contador de negativos)
                