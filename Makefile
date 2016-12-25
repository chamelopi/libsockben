CFLAGS=-std=c++11 -Wall -Wextra -Werror -pedantic

.PHONY=all clean

all: libsockben.so testsrv testcli

clean:
	rm -f *.o
	rm -f libsockben.so
	rm -f testsrv

libsockben.so: abstract_socket.o socket.o server_socket.o
	g++ $(CFLAGS) -o libsockben.so $^ -fPIC -shared

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $< -fPIC
	
testsrv: testsrv.o libsockben.so
	g++ $(CFLAGS) -L . -o testsrv testsrv.o -lsockben

testcli: testcli.o libsockben.so
	g++ $(CFLAGS) -L . -o testcli testcli.o -lsockben