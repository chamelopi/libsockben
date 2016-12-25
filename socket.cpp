#include "socket.h"
#include <iostream>

using namespace ben;

tcp_socket::tcp_socket(const char* addr, const char* srvc) : socket<tcp>(-1)
{
	struct addrinfo hints = {};
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	struct addrinfo* head;
	int status = getaddrinfo(addr, srvc, &hints, &head);
	if (status != 0)
	{
		throw std::runtime_error(gai_strerror(status));
	}
	
	int sock;
	struct addrinfo* curr;
	for (curr = head; curr != nullptr; curr = curr->ai_next)
	{
		sock = ::socket(curr->ai_family, curr->ai_socktype, curr->ai_protocol);
		if (sock == -1)
		{
			continue;
		}
		if (::connect(sock, curr->ai_addr, curr->ai_addrlen) != -1)
			break;
		::close(sock);
	}
	
	if (curr == nullptr)
	{
		freeaddrinfo(head);
		throw std::runtime_error("No usable address");
	}
	
	freeaddrinfo(head);
	this->sockfd = sock;
}
