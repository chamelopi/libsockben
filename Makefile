CFLAGS=-std=c++11 -Wall -Wextra -Werror -pedantic

.PHONY=all clean install

all: libsockben.so testsrv testcli

clean:
	rm -f *.o
	rm -f libsockben.so
	rm -f testsrv
	rm -f testcli

install: all
	install libsockben.so /usr/local/lib/libsockben.so
	mkdir -p /usr/local/include/ben
	install --target-directory=/usr/local/include/ben/ socket.h abstract_socket.h

uninstall:
	rm -f /usr/local/lib/libsockben.so
	rm -f /usr/local/include/ben/socket.h
	rm -f /usr/local/include/ben/abstract_socket.h
	# Remove include dir if empty
	rm -df /usr/local/include/ben

libsockben.so: abstract_socket.o socket.o server_socket.o
	g++ $(CFLAGS) -o libsockben.so $^ -fPIC -shared

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $< -fPIC

testsrv: testsrv.o libsockben.so
	g++ $(CFLAGS) -L . -o testsrv testsrv.o -lsockben

testcli: testcli.o libsockben.so
	g++ $(CFLAGS) -L . -o testcli testcli.o -lsockben
