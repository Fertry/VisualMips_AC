.config
    pipelined on;
    forwarding on;
    
.data
    x: .half 1,2,3,4,5,6,7,8,9,10
    y: .half 1,2,3,4,5,6,7,8,9,10
    z: .space 20
    a: .half 5
    
.text
    la $10, x
    la $20, y
    la $30, z
    la $31, a
    lh $5, 0($31)
    
    for:
        lh $11, 0($10)
        mul $11, $11, $5
        addi $10, $10, 2
        lh $21, 0($20)
        div $21, $5
        addi $20, $20, 2
        mfhi $21
        add $2, $11, $21
        sh $2, 0($30)
        addi $30, $30, 2
        bne $30, $31, for
        