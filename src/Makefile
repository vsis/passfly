CC=gcc

objs=rc4.o
tests=rc4.test.o

tests: $(objs) $(tests) tests.c
	$(CC) $(CFLAGS) -g tests.c -o tests $(objs) $(tests)

clean:
	rm -rf $(objs) $(tests) tests

