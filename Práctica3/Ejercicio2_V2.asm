.config
     delayed off
     
.data
    x:   .word 2 ,4,-6, 8,-10,12,-14, 16,-18, 20
    y:   .word 1,-2, 3,-4,  5,-6,  7, -8, -9,-10
    z:   .space 4

.text
    la  $10,x
    addi $20,$10,40
    addi $30,$10,80
rep:lw $21,0($20)
    lw $11,0($10)
    sub $11,$11,$21
    add $3,$3,$11
    addi $10,$10,4
    addi $20,$20,4
    bne $20,$30,rep
    sw $3, 0($30)