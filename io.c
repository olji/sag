#include "syscalls.h"
#include "io.h"
#include "str.h"

void print(char* s){
    int c = strlen(s);
    write(1,s,c);

}
void print_i(int i){

}
