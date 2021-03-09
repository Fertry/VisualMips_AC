.data; 
    op1:	.word 15;          
    op2:	.word 9; 
    res:	.space 4; 

.text
    la $2, op1; load address -> en $2 se carga op1  
    la $3, op2; load address -> en $3se carga op2 
    la $8, res; load address -> en $8 se carga res
    
    lw $4, 0($2); load sin desplazamiento
    lw $5, 0($3); load sin desplazamiento
    
    sub $6, $4, $5; resta $4 - $5 y lo carga en en $6, notese que se han cargado con lw en $4 y $5 previamente
    slt $7, $6, $0; compara el resultado (en $6) con $0 (que siempre es 0), si $6 es menor a 0, en $7 se carga un uno, en caso contrario, se carga un 0
    
    bne $7, $0, neg; si en $7 antes se cargo un 0 (porque $6 era mayor a 0), saltamos a la sig. instrucción, de lo contrario, en caso de que sea 1 ($6 < 0), saltamos a la etiqueta neg
    
    sw $6, 0($10); si $6 era mayor que 0, ahora se guarda (store) el resultado ($6) en $10 sin desplazamiento
    
    j fin; saltamos de forma incondicional a la etiqueta fin
    
neg: sw $0, 0($10); res se setea a 0

fin: