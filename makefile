
CC=g++
CFLAGS= -std=c++17
SRCS = src/dp.cpp

standard: $(SRCS)
	$(CC) -o $@.out $(CFLAGS) $^

simd: $(SRCS)
	$(CC) -o $@.out $(CFLAGS) -march=native -O3 $^

para: $(SRCS)
	$(CC) -DPARA $(CFLAGS) -o $@.out -fopenmp $^

simd_para: $(SRCS)
	$(CC) -DPARA -o $@.out $(CFLAGS) -fopenmp -march=native -O3 $^

clean:
	rm -f *.out