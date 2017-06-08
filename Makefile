PROJECT_NAME = sssg
CC = gcc
CCFLAGS = -nostdlib -Wpedantic -Wall -Werror -Wfatal-errors -g

sources = $(wildcard *.c)
existing_objs = $(wildcard *.o)
extra_objs = $(existing_objs) $(sources:.c=.o)
objects = $(sort $(extra_objs))
LIBS = -lgcc

all: $(objects)
	$(CC) $(CCFLAGS) $(LIBS) $(objects) -o $(PROJECT_NAME)

include $(sources:.c=.d)

# Create prerequesites (Nabbed from GNU makefile docs 
%.d: %.c
	@set -e; echo $@; \
	$(CC) -MM $(CCFLAGS) $< > $@.$$$$; \
	sed 's,\($&\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f $(PROJECT_NAME) $(BUILT_OBJS)
