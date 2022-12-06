

CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS= libgrades.so 
EXEC=prog.exe
RM=rm -fr *.o *.exe

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o prog.exe
libgrades.so: grades.h
	$(CC) $(CFLAGS) -c grades.c
clean:
	$(RM)   
