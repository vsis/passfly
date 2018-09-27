CC=gcc

objs=rc4.o
tests=rc4.test.c

run_test: $(objs) $(tests) run_test.c
	$(CC) $(CFLAGS) run_test.c -o run_test $(objs)
