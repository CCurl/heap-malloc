ARCH ?= 32

tests: tests.c heap.c heap.h
	$(CC) -m$(ARCH) -o tests tests.c heap.c

clean:
	rm ./tests

test: clean tests
	./tests
