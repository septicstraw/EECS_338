C = gcc -std=c99 
CFLAGS  = -g -Wall -lrt -lm -lpthread -fopenmp

all: problem1 problem2 problem3

problem1: problem1.o 
	$(CC) $(CFLAGS) -o problem1 problem1.o

problem1.o: problem1.c 
	$(CC) $(CFLAGS) -c problem1.c

problem2: problem2.o 
	$(CC) $(CFLAGS) -o problem2 problem2.o

problem2.o: problem2.c 
	$(CC) $(CFLAGS) -c problem2.c

problem3: problem3.o 
	$(CC) $(CFLAGS) -o problem3 problem3.o

problem3.o: problem3.c 
	$(CC) $(CFLAGS) -c problem3.c


clean: 
	$(RM) all *.o *~
