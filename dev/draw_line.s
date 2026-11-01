	.file	"draw.c"
	.text
	.globl	draw_line
	.type	draw_line, @function
    
#literal definition of spaghetti code



draw_line:
    # do some stupid 16 bit align for the stack for next time because why not i hate this
    push %rbx
    
    #int x0, int y0, int x1, int y1, uint8_t color
    #   %edi    %esi    %edx    %ecx      %r8b
    mov $0, %r10
draw_line_swap_innit:
    cmp %rdi, %rdx
    jge draw_line_swap_innit_cont
    #swap:
    push %rdi
    push %rdx
    pop %rdi
    pop %rdx
    push %rsi
    push %rcx
    pop %rsi
    pop %rcx
    draw_line_swap_innit_cont:

    mov %rcx, %rax
    sub %rsi, %rax #y1-y0
    shr $63, %rax
    shl $1, %rax
    add %rax, %r10
    cmp $0, %rax
    je draw_line_nonegate
        #negate y1 and y0
        not %rsi
        not %rcx
        inc %rsi
        inc %rcx
    draw_line_nonegate:
    #check if x and y need swapping:
         mov %rcx, %rax
         sub %rsi, %rax #deltay
         mov %rdx, %rbx
         sub %rdi, %rbx
         cmp %rax, %rbx
         jge draw_line_no_swap   
             inc %r10
             #swap x and ys
             push %rdi
             push %rsi
             pop %rdi
             pop %rsi
             
             push %rdx
             push %rcx
             pop %rdx
             pop %rcx
         draw_line_no_swap:
         push %r10
         push %rdi
         push %rsi
         push %rdx
         push %rcx
         push %r8
         call draw_line_drawer         
         pop %rbx
         ret

draw_line_drawer:
    #int x0, int y0, int x1, int y1, uint8_t color
    #   %edi    %esi    %edx    %ecx      %r8bd
    #mov -48(%rsp), 
    # x at %rax, y at %rbx, A at %rcx, B at %rdx, d at %r8
    #push m  48
    #push x0 40
    #push y0 32
    #push x1 24
    #push y1 16
    #push color 8
    
    #mov 24(%rsp), %rax
    #add 24(%rsp), %rax
    #mov %rax, 24(%rsp)
    #   48(%rsp) = flip thingie
    mov 40(%rsp), %rax #x0
    
    mov 32(%rsp), %rbx #y0
    
    mov 16(%rsp), %rcx #deltaY (A)
    sub 32(%rsp), %rcx
    
    mov 40(%rsp), %rdx #-deltaX (B)
    sub 24(%rsp), %rdx
    
    mov %rcx, %r8      #d initial
    add %rcx, %r8
    add %rdx, %r8
    
    draw_line_loop:
        #pretend i did  this correctly :)
        push %rax
        push %rbx
        push %rcx
        push %rdx
        push %r8
        
        
        
        mov 48(%rsp), %rdi #color
        mov %rax, %rdx #x
        mov %rbx, %rcx #y
        mov 88(%rsp), %r8 #flip/swap flags
        call plot_better
        
        
        pop %r8
        pop %rdx
        pop %rcx
        pop %rbx
        pop %rax
        
        cmp $0, %r8
        jle draw_line_loop_conditional_continue
        inc %rbx
        add %rdx, %r8 
        #add %rdx, %r8      
        draw_line_loop_conditional_continue:
        inc %rax
        add %rcx, %r8
        
        cmp 24(%rsp), %rax
        jle draw_line_loop
        
        ret $48
    
plot_better:
    #color x    y    m
    #rdi   rdx  rcx  r8
    #m:  ...000XX
    #          ||
    # negate y_||_swap x and y
    #check for swap x and y:
    mov %r8, %rax
    and $1, %rax
    cmp $0, %rax
    je plot_better_noswap
    #swap x and y:
        push %rcx
        push %rdx
        pop %rcx
        pop %rdx
    plot_better_noswap:
        
    #isolate negate bool
    mov %r8, %rax
    shr $1, %rax
    cmp $0, %rax #if 1:negate
    je plot_better_nonegate
    #negate:
        not %rcx
        inc %rcx
    plot_better_nonegate:
    #vga_set_pixel(uint8_t color, size_t x, size_t y)
    mov %rdx, %rsi
    mov %rcx, %rdx
    sub $8, %rsp #align stack for C call
    call vga_set_pixel
    add $8, %rsp
    ret