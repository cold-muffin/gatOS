.section .text
.code32

.global interrupt_test_stub
.extern interrupt_test_handler

interrupt_test_stub:
    pusha
    call interrupt_test_handler
    popa
    iret