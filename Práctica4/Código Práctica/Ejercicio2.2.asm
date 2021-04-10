.config
    pipelined on 
    forwarding on
    delayed on
    
.data

.text

    addi $10, $10, 0
    addi $20, $10, 80
    addi $30, $20, 156
    
bucle: lw $11, 0($10)
       addi $10, $10, 4
       sll $11, $11, 3
       lw $21, 0($20)
       addi $30, $30, -4
       sub $11, $11, $21
       slt $1, $20, $30
       addi $20, $20, 4
       bne $1, $0, bucle
       sw $11, 4($30)
       sw $0, 0($10)