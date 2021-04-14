.config
     readprotect off
     split on
     dcache size=4096 block=256 way=2
 
.text
     lb $2, 0x100009AA
     lb $2, 305420000; 16782848
     lb $2, 12345678
     lb $2, 0x12345678