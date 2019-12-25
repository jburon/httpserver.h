.PHONY: test clean

all: httpserver.h

test: http-server

http-server: test/main.c httpserver.h
	$(CC) $(CFLAGS) -O3 test/main.c -o http-server

fuzz_cli: fuzz/fuzz_request.c fuzz/fuzz_util.c httpserver.h
	$(CC) $(CFLAGS) -O3 fuzz/fuzz_request.c fuzz/test/fuzz_cli.c fuzz/fuzz_util.c -o fuzz_cli

clean:
	@rm http-server request
