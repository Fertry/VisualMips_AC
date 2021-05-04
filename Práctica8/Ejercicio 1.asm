.config
        readprotect off
        writeprotect off
        pipelined off
        split off
        cache  64 8 1 cbwa lru ; Config Caché de datos
    
.text 0x00401404
        addi $2, $0, 0x0290    
        addi $3, $2, 8
        addi $5, $0, 0
loop:   lb $10, 0($2)
        add $5, $5,$10
        addi $2,$2,1
        slt $4, $2,$3
        bne $4,$0, loop
