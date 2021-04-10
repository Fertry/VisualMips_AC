.config
    pipelined on 
    forwarding on
    delayed on
    
.data

.text

    addi $3, $0, 3
    addi $2, $0, 36
    addi $10, $0, 0
    
    for: lw $5, 4($10)
         addi $10, $10, 4
         slt $4, $10, $2
         add $1, $5, $3
         bne $4, $0, for
         sw $1, -4($10)
         sw $0, 0($10)
         
         