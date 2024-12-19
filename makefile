ARCH ?= 32

tests: tests.c hp_malloc.c hp_malloc.h
	$(CC) -m$(ARCH) -o tests tests.c hp_malloc.c

clean:
	rm ./tests

test: clean tests
	./tests
