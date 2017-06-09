#include "syscalls.h"
int main(int, char**);

void _start(){
    int argc;
    char **argv;
    asm("movl (%%rbp), %0\n\t"
            "movq (%%rbp), %1"
            :"=r"(argc), "=r"(argv)
            );
    char count = argc + 0x30;
    write(1, &count, 1);

    long retcode = main(argc, argv);
    exit(retcode);
}
int main(int argc, char **argv){
    return 0;
}
