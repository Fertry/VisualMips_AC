.config
    pipelined on 
    forwarding on
    delayed on
    
.data
    x: .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
    y: .word 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    z: .space 80

.text
    ;addi $10, $10, 0
    li $10, 0x10000000
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