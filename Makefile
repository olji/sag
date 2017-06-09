PROJECT_NAME = sag
CC = gcc
CFLAGS = -nostdlib -Wpedantic -Wall -Werror -Wfatal-errors -g -Wno-builtin-declaration-mismatch

sources = $(wildcard *.c)
existing_objs = $(wildcard *.o)
extra_objs = $(existing_objs) $(sources:.c=.o)
objects = $(sort $(extra_objs))
LIBS = -lgcc

all: $(objects)
	$(CC) $(CFLAGS) $(LIBS) $(objects) -o $(PROJECT_NAME)
asm: $(objects)
	$(CC) -S sssg.c

include $(sources:.c=.d)

# Create prerequesites (Nabbed from GNU makefile docs 
%.d: %.c
	@set -e; echo $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($&\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f $(PROJECT_NAME) $(BUILT_OBJS)
