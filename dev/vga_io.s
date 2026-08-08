.global outb
.type outb, @function

outb:
    mov 4(%esp), %edx
    mov 8(%esp), %eax
    outb %al, %dx
    ret


.global inb
.type inb, @function

inb:
    mov 4(%esp), %edx
    inb %dx, %al
    movzbl %al, %eax
    ret