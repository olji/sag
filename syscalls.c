#include "syscalls.h"
#include "io.h"

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
int read(int file, char *str, int len){
    int ret = 0;
    asm("movq $0x00, %%rax\n\t"
        "movl %1, %%edi\n\t"
        "movq %2, %%rsi\n\t"
        "movl %3, %%edx\n\t"
        "syscall"
        :"=r"(ret)
        :"r"(file),"r"(str),"r"(len)
        :"%rax","%rdi","%rsi","%rdx"
        );
    return 1;
}
void exit(long exitcode){
    asm("movq $0x3C, %%rax\n\t"
        "movq %0, %%rdi\n\t"
        "syscall"
        :
        :"r"(exitcode)
        :"%rax","%rdi"
       );
}
void *mmap(long length, int prot, int flag, int fd, long offset){
    void *addr = 0;
    asm("movq $0x09, %%rax\n\t"
        "movq $0x0, %%rdi\n\t"
        "movq %1, %%rsi\n\t"
        "movl %2, %%edx\n\t"
        "movl %3, %%r10d\n\t"
        "movl %4, %%r8d\n\t"
        "movq %5, %%r9\n\t"
        "syscall\n\t"
        "movq %%rax, %0\n\t"
        :"=r"(addr)
        :"r"(length), "r"(prot), "r"(flag), "r"(fd), "r"(offset)
        :"%rax","%rdi","rsi","rdx","r10","r8","r9"
       );
    return addr;
}
void *brk(void *addr){
    void *ret;
    asm("movq $0x0C, %%rax\n\t"
        "movq %1, %%rdi\n\t"
        "syscall\n\t"
        "movq %%rax, %0"
        :"=r"(ret)
        :"r"(addr)
        :"%rax","%rdi"
       );
    return ret;
}
int open(char *path, int flags, int mode){
    int ret;
    asm("movq $0x02, %%rax\n\t"
        "movq %1, %%rdi\n\t"
        "movl %2, %%edx\n\t"
        "movl %3, %%r10d\n\t"
        "syscall\n\t"
        "movl %%eax, %0"
        :"=r"(ret)
        :"r"(path),"r"(flags),"r"(mode)
        :"%rax","%rdi","edx","r10"
        );
    return ret;
}
int creat(char *path, int mode){
    int ret;
    asm("movq $0x02, %%rax\n\t"
        "movq %1, %%rdi\n\t"
        "movl $00100, %%edx\n\t"
        "movl %2, %%r10d\n\t"
        "syscall\n\t"
        "movl %%eax, %0"
        :"=r"(ret)
        :"r"(path),"r"(mode)
        :"%rax","%rdi","edx","r10"
        );
    return ret;
}
int lseek(int fd, long offset, int whence){
    int ret;
    asm("movq $0x08, %%rax\n\t"
        "movl %1, %%edi\n\t"
        "movq %2, %%rdx\n\t"
        "movl %3, %%r10d\n\t"
        "syscall\n\t"
        "movl %%eax, %0"
        :"=r"(ret)
        :"r"(fd),"r"(offset),"r"(whence)
        :"%rax","%rdi","edx","r10"
        );
    return ret;
}
int close(int fd){
    int ret;
    asm("movq $0x03, %%rax\n\t"
        "movl %1, %%edi\n\t"
        "syscall\n\t"
        "movl %%eax, %0"
        :"=r"(ret)
        :"r"(fd)
        :"%rax","%rdi"
        );
    return ret;
}
