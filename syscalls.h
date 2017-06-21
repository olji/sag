#ifndef SYSCALLS_H
#define SYSCALLS_H

/* Glorious platform dependencies */
#define PAGESIZE 4096

void exit(long retcode);
int write(long file, char *str, long len);
int read(int file, char *str, int len);
void *mmap(long length, int prot, int flag, int fd, long offset);
void *brk(void *addr);
int open(char *path, int flags, int mode);
int close(int fd);
int creat(char *path, int mode);
int lseek(int fd, long offset, int whence);

#endif
