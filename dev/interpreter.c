/*
each instruction is a pointer to the function in the kernel and an operand
*/

void execute(size_t* instruction) {
    void (*command)(size_t);
    command = *instruction;
    command(*instruction+sizeof(size_t));
}

//The instructions:

void push(size_t in) {
    
}