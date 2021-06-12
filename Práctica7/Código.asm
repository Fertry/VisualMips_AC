.eqv    LONG_VECTOR   256
.eqv    ZANCADA       8
.eqv    TAM_CACHE     256
.eqv    TAM_BLOQUE    16     
.eqv    NUM_VIAS      1
.eqv    P_ESCRIT      cbwa   ;cbwa   o   wtnwa
.eqv    P_REEMPL      lru    ;random, lru, fifo, lfu
.config
        readprotect off
        split on                ; Cachés separadas
        dcache TAM_CACHE TAM_BLOQUE NUM_VIAS P_ESCRIT P_REEMPL ; Config Caché de datos.
.data    
v:      .space LONG_VECTOR
.text
        li $5,0
        li $7,LONG_VECTOR
i:      
        lb   $6, 0($5)          	; Lee x[i]
        addi $6,$6,5 				; Suma 5
        sb   $6, 256($5)     		; Escribe en y[i]
        addi $5,$5,ZANCADA			; Incrementa el índice
        blt $5,$7,i             	; ¿Fin Vector?
