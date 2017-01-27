#include "socket.h"
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

/**
 * Test program for server sockets
 */
int main(void)
{
	try
	{
		ben::tcp_server_socket srv(1337);
		int a = 42;

		cout << "Waiting ..." << endl;

		string clientip;
		ben::tcp_socket cl = srv.accept(clientip);
		
		cout << "Accepted connection from " << clientip << "." << endl;
		
		char buf1[6] = {'a', 'b', 'c', 'd', 'e'};
		char buf2[6];
		string buf;
		string hw("Hello, World!");
		cl.sendln(hw);
		cl.recvln(buf);
		cl.sendln(buf);
		
		cl.send(buf1, 6);
		cl.recv(buf2, 6);
		
		cl << buf << a;
		cout << buf << a;
		cl >> buf;
		cout << buf;
	}
	catch(runtime_error& e)
	{
		cerr << "Exception occured: " << e.what() << endl;
	}
}
