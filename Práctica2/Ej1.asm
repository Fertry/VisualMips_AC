.config
    pipelined on;
    forwarding on;
    
.data
    x: .word -123, 321, -234, 432, -345, 543, -456, 654;
    
.text
    add $2,$0,$0
    lui $3,0x1000
    ori $3,$3,0x0000
    addi $4,$3,32
    
    bucle:
        lw $5,0($3)
        addi $3,$3,4
        add $2,$2,$5
        bne $3,$4,bucle
        sra $2,$2,3
        sw $2,0($4)
        
    