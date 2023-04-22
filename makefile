
CC=g++
CFLAGS= -std=c++17
SRCS = src/dp.cpp

standard: $(SRCS)
	$(CC) -o $@.out $(CFLAGS) $^

simd: $(SRCS)
	$(CC) -o $@.out $(CFLAGS) -march=native -O3 $^

clean:
	rm -f *.out