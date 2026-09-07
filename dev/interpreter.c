/*
each instruction is a pointer to the function in the kernel and an operand
*/

void execute(size_t* instruction) {
    void (*command)(size_t);
    command = *instruction;
    command(*instruction+sizeof(size_t));
}

/*The instructions:
im gonna assume the assembler makes memory like this:
|head||program and instructions||initial alloation|
|||||||||||||||||||||||||||||||||||||||||||||||||||
so the unallocated space is free for the taking. I'll assign a one element array and use that as a starting pointer for the rest. I know in assembly I just put that in the .bss. 
*/
size_t* startptr = *{0};
size_t* nonkernelstart = 1024; // is size_t 32bits? (4bytes)
/*I need some memory for the kernel to keep track of stuff.
so I'll give 4kb to the kernel for now.
so I'll allocate like this: 
Kernel memory:
0kb          1kb           2kb           3kb     4kb
|active proc||passive proc||empty allocs||  ?    |
||||||||||||||||||||||||||||||||||||||||||||||||||
*/
typedef struct {
    size_t size;     //length of the section
    size_t pointer;  //start pointer
    size_t returnTo; //when a process jumps back to this, where to return to.
    size_t instructionsDone; //for process switching
} allocation;
void allocate(size_t size) {
    // needs to go through empty allocs and find the smallest one that is bigger than the requested size
    //then needs to split that into an allocated part and leave the unallocated part
    //if the part that remains has a size of 0 then it gets deleted and everything after has to be shifted down (so it's o(n) but that's fine. there isn't much to go through.)
}
void free(size_t pointer) {
    //has to go through the active and passive procs lists to find the correct allocation
    //has to look for a neighbor allocation in the empty part
    //if none is found it should be appended to empty and otherwise update a neighbor to include it.
    //then delete itself from an allocated list and shift everything down.
}


//==============================================================================
/*this is where the interpreter itself starts. besides the existence of this there needs to be a way to launch the first process that launches others so there will be (in storage) a startup program that can launch a terminal or a gui or other stuff and that can be configured later.
So in an allocation the first few bytes are the registers and info like:
(btw other programs cannot modify this)
    *where the stack starts
    *where the stack ends
    *permissions for other programs regarding this one
    *???
when a new process is started, the file is read from storage and a header like above is constructed and the file header dictates the size of the allocation. 
Programs can launch other processes. 

holy shit this is a lot to implement....
the interpreter will have ways of interacting with the hal with inb and outb. I'll have most important assembly features.
-----------
As seen by the execute() fn, the instructions will have a pointer to the instruction which will be handled by a built in assembler which can just access the functions because this is one big c thingie. 
so I need to also make:

    *finish interpreter //this should be fairly simple for now
    *filesystem driver //oy oy oy
    *assembler          //this should be not very hard
    *keyboard and mouse once basic functions work    //There is some complication here because it will expose bugs in the filesystem and interpreter
    *then a C compiler for this system but written in the interpreted assembly bytecode thing (my stupid compiler project is useful here :)    //  this will take a long time and be like a side quest. maybe gpt can do this fast...
    *after that, a terminal and shell     // not very hard I  think
////This is the point at which the kernel is done
    *at that point, I can start making programs to make this somewhat usable   
    *later, a gui which should be not that hard because I have the graphics driver done so custom charactrers and sprites are easy.

Here is the interpreter:
*/

typedef struct {
    size_t r1;
    size_t r2;
    size_t r3;
    size_t r4;
    size_t r5;
    size_t r6;
    size_t r7;
    size_t r8;
    size_t rip; //isntruction pointer
    size_t rf;  //flag
    size_t rbp; //base pointer
    size_t rsp; //stack pointer
    size_t whereStackEnds;
    size_t whereStackStarts; //ill add more later
} procHeader;
//idea is procHeader is changed by everything
//======================================================================================
//Also I just realized im gonna have 3 stacks shiiiiit
//======================================================================================
void push(size_t in) {
    
}