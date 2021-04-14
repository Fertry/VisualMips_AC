.config
     readprotect off
     split on
     dcache size=64 block=8 way=2 ; Caché de 64bytes, 2 vías y bloques de 8 bytes
     
.text
     li $10, 0x10000000
     addi $20,$10, 64
     rep: lb $5, 0($10)
          addi $10,$10, 8 ; Valor de ZANCADA
          bne $10,$20, rep