CC=gcc
CFLAGS=-I.

gptbn: gptbn.o
     $(CC) -o gptbn gptbn.o -I.
