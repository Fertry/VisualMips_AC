.config
    pipelined on 
    forwarding on
    delayed on
    
.data
    x: .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
    y: .word 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    z: .space 80

.text

    addi $3, $0, 3
    addi $2, $0, 36
    li $10, 0x10000000
    ;addi $10, $0, 0
    
    for: lw $5, 4($10)
         addi $10, $10, 4
         slt $4, $10, $2
         add $1, $5, $3
         bne $4, $0, for
         sw $1, -4($10)
         sw $0, 0($10)
         
         