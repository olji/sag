#include "syscalls.h"

int write(long file, char *str, long len){
    int ret = 0;
    asm("movq $0x01, %%rax\n\t"
        "movq %1, %%rdi\n\t"
        "movq %2, %%rsi\n\t"
        "movq %3, %%rdx\n\t"
        "syscall"
        :"=r"(ret)
        :"r"(file),"r"(str),"r"(len)
        :"%rax","%rdi","%rsi","%rdx"
        );
    return 1;
}
void exit(long exitcode){
    write(1, "\nExiting\n", 9);
    asm("movq $0x3C, %%rax\n\t"
        "movq %0, %%rdi\n\t"
        "syscall"
        :
        :"r"(exitcode)
        :"%rax","%rdi"
       );
}
