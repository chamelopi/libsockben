# libsockben

Primitive object-oriented socket library for C++11. It currently supports
IPv4 TCP and UDP sockets on the Linux/Unix platform.

Example code for the client side:

```c++
#include <iostream>
#include <string>
#include <ben/socket.h>

int main(void) {
  ben::socket<ben::tcp> sock("google.com", "80");
  // When writing std::string, \n is inserted automatically
  sock << "GET / HTTP/1.0\r";
  std::string line;
  do {
    sock >> line;
    std::cout << line;
  } while (line != "\r");

  return 0;
}
```
