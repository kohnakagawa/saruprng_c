TARGET = c.out

all: ${TARGET}

c.out: test.c
	gcc -std=c99 -Wall -Wextra -O3 $< -lm -o $@

clean:
	rm -f ${TARGET} result_c.dat Rplots.pdf

test: ${TARGET}
	./c.out > result_c.dat
	R --slave --vanilla < showdist.R

