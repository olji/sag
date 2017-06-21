#include <stdio.h>
#include "syscalls.h"
#include "str.h"
#include "io.h"
int main(int, char**);

void _start(){
    long argc;
    char **argv;
    asm("movq 0x08(%%rbp), %0\n\t"
        "leaq 0x08(%%rbp, %%rsi, 0x8), %1"
        :"=r"(argc), "=r"(argv)
       );
    /* leaq instruction fetched argv with one char* offset, adjust that through incrementation, can't be arsed to fix the formula */
    ++argv;

    long retcode = main(argc, argv);
    exit(retcode);
}
int main(int argc, char **argv){
    if (argc < 3){
        print("Usage: sag NOTECOL_NAME ACTION [STRING]\n\nExamples:\n`sag work new \"quit job\"`\n\tAdd \"quit job\" to the note collection 'job', creating if not present\n`sag work get`\n\tOutput all notes from collection 'work' to stdout.\n");
        return 1;
    }

    void *brk0 = brk(0);
    /* Move break up one page */
    char *page0 = brk0;
    void *brk1 = brk(page0 + 1);
    char *path = page0;
    if (brk1 == 0){
        print("Sadness\n");
    }
    append(path, "/home/olji/.sag/");
    append(path, argv[1]);


    if (strcmp(argv[2],"new")){
        if (argc < 4){
            print("No input given. (I'm not reading from stdin)\n");
            return 1;
        }

FILE_OPEN:;
        /* (O_APPEND | O_RDWR) = 002002 */
        int fd = open(path, 002002, 002);
        if (fd < 0){
            open(path, 00700, 00666);
            goto FILE_OPEN;
        }

        write(fd, argv[3], strlen(argv[3]));
        write(fd, "\n", 1);
        close(fd);
    } else if (strcmp(argv[2], "get")){
        int fd = open(path, 000, 0);
        int offset = lseek(fd, 2, 0);
        lseek(fd, 0, 0);
        char *read_str = path;
        if (offset >= PAGE_SIZE){
            int pages = (offset / 4096) + 1;
            brk(page0+(pages*4096) + 1);
        }
        read(fd, read_str, offset);
        print(read_str);
        print("\n");
    }
    return 0;
}
