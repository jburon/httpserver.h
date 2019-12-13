.PHONY: test clean

all: httpserver.h

test: http-server

http-server: test/main.c httpserver.h
	$(CC) $(CFLAGS) -O3 test/main.c -o http-server

request: fuzz/request.c httpserver.h
	$(CC) $(CFLAGS) -O3 fuzz/request.c -o request

clean:
	@rm http-server request
