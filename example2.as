
.extern wNumber
STR:   .asciz    "aBcd"
MAIN: add       $3,$5 , $9
LOOP: ori $9,-5,$2
        jmp     Next
Next:   moveAA    $20,$4
5LIST:   .db     6,-9
        bgt     $4,$2,END
  ;      la      K




        sw      $0,4,    $10
        bneAA     $444,$9,LOOP
        jmp     $4
 .extern   vall
        .dh     27056
    K:  .dw     31, -12
    END:    stop