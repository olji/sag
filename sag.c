#include "syscalls.h"
int main(int, char**);

void _start(){
    long argc;
    char **argv;
    asm("movq 0x08(%%rbp), %0\n\t"
        "leaq 0x08(%%rbp, %%rsi, 0x8), %1"
        :"=r"(argc), "=r"(argv)
       );
    /* leaq instruction fetched argv with one char* offset, adjust that through incrementation */
    ++argv;

    long retcode = main(argc, argv);
    exit(retcode);
}
int main(int argc, char **argv){
    if (argc < 2){
        write(1, "Expected more from you\n", 23);
    }
    return 0;
}
