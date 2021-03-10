;  Implementar el siguiente código C en MIPS
;        …
;        aux = 0;
;        for(i=0; i<10; i++)
;        {
;        	aux = aux + x[i];
;        }
;        aux = aux/10;
;        res = aux;
;        …
 
.data
	x:      .half 6, -4, 15, 9, -2, 11, 8, 20, 5, 2
	res:    .space 2						; El resultado debería dar 70

.text
	la $2, x	; Dirección inicial del vector (y, por tanto, del primer elemento)
	la $10, res	; Dirección de “res” (donde almacenar el resultado final)
       