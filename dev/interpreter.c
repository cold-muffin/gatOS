void write_file(char* buffer, char* name) {}
void read_file(char* buffer, char* name) {}
void exec_file(char* name) {}
struct allocations {
    char* piece,
    size_t size,
}allocations;
void alloc(char** allocations, size_t size) {}
void free(char* ptr) {}
void get_partition_size(char* allocation) {}