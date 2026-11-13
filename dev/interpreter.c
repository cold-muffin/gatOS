#include <stdint.h>
#include <stddef.h>
/*
====================================================================================================
                                x86 / x86-64 SEGMENT & POINTER REGISTERS
====================================================================================================
Register | Name            | Size   | Primary Purpose & Behavior
---------+-----------------+--------+---------------------------------------------------------------
  %cs    | Code Segment    | 16-bit | Points to executable instructions. Holds Current Privilege 

         |                 |        | Level (CPL) in lowest 2 bits. Paired with IP/EIP/RIP.
---------+-----------------+--------+---------------------------------------------------------------
  %ds    | Data Segment    | 16-bit | Default segment for general data access (variables, arrays).

         |                 |        | Base is forced to 0 in 64-bit long mode.
---------+-----------------+--------+---------------------------------------------------------------
  %ss    | Stack Segment   | 16-bit | Points to the program stack. Paired with SP/ESP/RSP. 

         |                 |        | Base is forced to 0 in 64-bit long mode.
---------+-----------------+--------+---------------------------------------------------------------
  %es    | Extra Segment   | 16-bit | Auxiliary data segment, often used as the destination 

         |                 |        | segment in string operations (e.g., movsb, stosb).
---------+-----------------+--------+---------------------------------------------------------------
  %fs    | FS Segment      | 16-bit | General extra segment. Actively used in 32/64-bit OSes for 

         |                 |        | Thread-Local Storage (TLS) and Windows TEB structures.
---------+-----------------+--------+---------------------------------------------------------------
  %gs    | GS Segment      | 16-bit | General extra segment. Actively used in 64-bit OSes for 

         |                 |        | kernel data structures (Linux) or TLS (Windows/macOS).
====================================================================================================
  %ip    | Instruction Ptr | 16-bit | Offset of next instruction in 16-bit mode (paired with %cs).
  %eip   | Extended IP     | 32-bit | Offset of next instruction in 32-bit mode (paired with %cs).
  %rip   | 64-bit IP       | 64-bit | Address of next instruction in 64-bit mode; supports 

         |                 |        | RIP-relative addressing for position-independent code.
====================================================================================================
*/
typedef struct {
    void* start;
    size_t len;
} alloc;
static alloc active_allocations[10000];//max
static alloc passive_allocations[10000];//max


//(cahtgpt) just linux
/*
void write_file(char* buffer, char* name) {}
void read_file(char* buffer, char* name) {}


void assemble(char* name) {
    
}

//starter
//loop:
//    copy instr;
//    if its a mem read then check if it is allowed
//    
//we need lock in
void exec_file(char* name) {
    
}



void alloc(char** allocations, size_t size) {

}

void free(char* ptr) {

}

void get_partition_size(char* allocation) {

}

*/