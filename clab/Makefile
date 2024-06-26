#
# Simple Makefile to build the programs
#
# Eleanor Birrell
# Pomona College
# January 21, 2020
#
CC = gcc

all:
	echo "no default action; specify a program"

q1: q1.c
	$(CC) -o q1 q1.c 

q2: q2.c
	$(CC) -g -o q2 q2.c

q3: q3a.c q3b.c
	$(CC) -g -o q3a q3a.c
	$(CC) -g -o q3b q3b.c

q4: q4.c
	$(CC) -o q4 q4.c

q5: q5.c
	$(CC) -o q5 q5.c

clean:
	rm -rf q1 q2 q3a q3b q4 q5
	rm -rf *~
	rm -rf *.dSYM