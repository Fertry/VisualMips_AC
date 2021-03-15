; Código de ejemplo para el cálculo del tiempo de ejecución
; Práctica 2 AC - Boletín 

.config 
    pipelined on;
    forwarding on;
    delayed off; 
    
.data
    datos: .word 1,3,5,7,9,11,13,15,17,19,21,0;
    
.text
    la $10, datos;
    
    rep:
        lw $5, 0($10);
        beq $5, $0, fin;
        sra $5, $5, 1;
        sw $5, 0($10);
        addiu $10, $10, 4;
        j rep;
        
    fin: