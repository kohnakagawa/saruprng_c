TARGET = cpp.out c.out

all: ${TARGET}

cpp.out: test.cpp
	g++ -Wall -Wextra -O3 $< -o $@

c.out: test.c
	gcc -std=c99 -Wall -Wextra -O3 $< -o $@

clean:
	rm -f ${TARGET} result_c.dat result_cpp.dat

test: ${TARGET}
	./cpp.out > result_cpp.dat
	./c.out > result_c.dat
	diff result_cpp.dat result_c.dat

