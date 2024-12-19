CC = clang

tests: tests.c hp_malloc.c hp_malloc.h
	$(CC) -o tests tests.c hp_malloc.c

test: tests
	./tests
		