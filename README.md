# libsockben

Primitive object-oriented socket library for C++11. It currently supports
IPv4 TCP and UDP sockets on the Linux/Unix platform.

Example code for the client side:

```c++
#include <ben/socket.h>

using namespace ben;

int main(void) {
  socket<tcp> sock("google.com", "80");
  // When writing std::string, \n is inserted automatically
  sock << "GET / HTTP/1.0\r";
  do {
    std::string line;
    sock >> line;
    std::cout << line;
  } while (line != "\r");
}
```
