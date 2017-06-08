#!/bin/sh

printf "#include <sys/syscall.h>\n$1" | gcc -E - | tail -n1
