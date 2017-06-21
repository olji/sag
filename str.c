#include "str.h"
#include "syscalls.h"

int strlen(char* s){
    int i = 0;
    while (s[i] != 0){
        ++i;
    }
    return i;
}
char* itos(int digit){
    /* Malloc needs to be implemented before this works properly */
    char *str = "";
    int len = isize(digit);
    int filter = 1;
    for(int i = 1; i < len; ++i){
        filter *= 10;
    }
    int number;
    for(int i = 0; i < len; ++i){
        number = digit / filter;
        digit %= filter;
        /* append to string */
        char c = number + 0x30;
        write(1,&c,1);
        filter /= 10;
    }
    return str;
}

int isize(int digit){
    int tenth = 1;
    int digits = 0;
    while (digit / tenth != 0){
        tenth *= 10;
        ++digits;
    }
    return digits;
}
int append(char *dest, char *src){
    int j = strlen(dest);
    int i = 0;
    for(; i < strlen(src); ++i){
        dest[j+i] = src[i];
    }
    return i;
}
int strcmp(char *a,char *b){
    if (strlen(a) != strlen(b)){
        return 0;
    }
    for(int i = 0; i < strlen(a); ++i){
        if (a[i] != b[i]){
            return 0;
        }
    }
    return 1;
}
