# libsockben

Primitive object-oriented socket library for C++11. It currently supports
IPv4 TCP and UDP sockets on the Linux/Unix platform.

## Installation

To install, do
```
$ make
$ sudo make install
```

This places the library in `/usr/lib` and the header files in `/usr/include/ben`.

To remove, do
```
$ sudo make uninstall
```

## Usage

Example code for the client side (Retrieve HTTP header):

```c++
#include <iostream>
#include <string>
#include <ben/socket.h>

int main(void) {
  ben::tcp_socket sock("google.com", "80");
  sock << "GET / HTTP/1.0\r\n\r\n";
  std::cout << "Sent request" << std::endl;

  std::string line;
  do {
    sock >> line;
    std::cout << line;
  } while (line != "\r\n");

  return 0;
}
```

Example code for server side (Present a hello world message to a connecting client):

```c++
#include <iostream>
#include <string>
#include <ben/socket.h>

int main(void) {
  ben::tcp_server_socket serv(1337);
  while (true) {
    std::string addr;
    ben::tcp_socket client = serv.accept(addr);
    client << "Hello " << addr << "!\n";
    client.close();
  }
}
```
