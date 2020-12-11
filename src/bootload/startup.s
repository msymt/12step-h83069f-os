    .h8300h
    .section .text
    .global _start
#   .type   _start,@function
_start:                     #   define "_start" label
    mov.l   #_stack,sp      #   stack pointer
    jsr     @_main          #   main function
1:
    bra 1b
