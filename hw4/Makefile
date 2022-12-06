

CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
RM=rm -fr *.o *.exe

all: prog.exe libgrades.so grades.o
libgrades.so: grades.o linked-list.h  
	$(CCLINK) -shared grades.o -o libgrades.so llinked-list -L.
prog.exe: grades.o
	$(CCLINK) grades.o -o prog.exe -lgrades -L.
grades.o: grades.h grades.c linked-list.h libgrades.so
	$(CC) $(CFLAGS) -c -fpic grades.c
clean:
	$(RM)   



