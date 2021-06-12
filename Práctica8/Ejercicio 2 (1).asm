.eqv    SEGMENTADO    off
.eqv    SEPARADA      off
.eqv    TAM_CACHE     256

.eqv    DirPrograma 0x00401404
.eqv    DirDatos    0x0238
.eqv    TamVector     200
.eqv    PENALIZFALLO  8
.eqv    REPETICIONES  2
.config
       readprotect off
       writeprotect off
       pipelined SEGMENTADO
       split SEPARADA
       memory PENALIZFALLO
       cache  TAM_CACHE 8 1 cbwa lru ; Config Caché de datos
       dcache TAM_CACHE 8 1 cbwa lru ; Config Caché de datos
       icache TAM_CACHE 8 1 cbwa lru ; Config Caché de instrucciones
.text DirPrograma
       addi $8, $0, REPETICIONES
       addi $2, $0, DirDatos
       addi $3, $2, TamVector
       addi $5, $0, 0
loop:	lb $10, 0($2)
       addi $2,$2,1
       slt $4, $2,$3
       add $5,$5,$10
       bne $4,$0, loop
       addi $8,$8,-1
       addi $2, $0, DirDatos
       bne $8,$0, loop