.config
    pipelined on 
    forwarding on
    delayed off
    
.data


.text

     li $10, 0x10000100 ; dir. inicial de “x”
     addi $20, $10, 40 ; dir. inicial de “y”
     addi $30, $20, 40 ; dir. inicial de “z”
     addi $5, $30, 40 ; final de “z"
     addi $25, $0, 3
    for:
     lw $3, 0($20)
     lw $2, 0($10)
     mul $2, $2, $25
     add $2, $2, $3
     sw $2, 0($30)
     addi $10, $10, 4
     addi $20, $20, 4
     addi $30, $30, 4
     bne $30, $5, for