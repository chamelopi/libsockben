#include "socket.h" 
#include <iostream>

using namespace std;


/**
 * Test program for client sockets
 */
int main(void)
{
	try
	{
		string buf;
		ben::tcp_socket sock("localhost", "1337");
		
		sock.recvln(buf);
		cout << buf << endl;
		
		string text;
		cout << "> ";
		cin >> text;
		sock.sendln(text);
		
		sock.recvln(buf);
		cout << buf;
		
		char buf2[6];
		sock.recv(buf2, 6);
		cout << buf2 << endl;
		sock.send(buf2, 6);
		
		assert(strncmp(buf2, "abcde", 5) == 0);
		assert(buf == text);
		
		sock.close();
	}
	catch(runtime_error& e)
	{
		cerr << "Exception occured: " << e.what() << endl;
	}
}