# This is a reference Makefile for you benefit.
# to use the Makefile, you run:
# make first - this compiles the C file into an executable named first
# make clean - will delete first
# These are variables, so you don't have to write gcc and "-fsanitize=address,undefined -Og -g -Wall -Werror -std=c11" over and over again.
CC=gcc
CFLAG = -fsanitize=address,undefined -Og -g -Wall -Werror -std=c11

# This command tells us:
# to make the executable named first, we need first.c. If we have first.c, we can make 
# first by running:
# gcc -o first first.c -fsanitize=address,undefined -Og -g -Wall -Werror -std=c11
first: first.c 
	$(CC) -o first first.c $(CFLAG)
clean: first # This is the clean command, which will remove the first executable
	rm -f first
