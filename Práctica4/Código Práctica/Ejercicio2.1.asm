.config
    pipelined on 
    forwarding on
    delayed off
    
.data

.text

    addi $10, $10, 0
    addi $20, $10, 80
    addi $30, $20, 156
    
bucle: lw $11, 0($10)
       sll $11, $11, 3
       lw $21, 0($20)
       sub $11, $11, $21
       sw $11, 0($30)
       addi $10, $10, 4
       addi $20, $20, 4
       addi $30, $30, -4
       slt $1, $20, $30
       bne $1, $0, bucle
       sw $0, 0($10) 
        
    
    