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