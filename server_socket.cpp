#include "socket.h"

using namespace ben;

tcp_server_socket::tcp_server_socket(short port)
{
	struct sockaddr_in name = {};
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	
	this->sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockfd == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	
	// Reuse addresses
	int flag = 1;
	setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
	
	if (::bind(this->sockfd, (struct sockaddr*) &name, sizeof(name)) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	
	if (::listen(this->sockfd, SOMAXCONN) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
}

tcp_socket tcp_server_socket::accept()
{
	int fd = ::accept(this->sockfd, nullptr, nullptr);
	if (fd == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	
	return tcp_socket(fd);
}

tcp_socket tcp_server_socket::accept(std::string& ip)
{
	struct sockaddr addr;
	socklen_t addrlen = sizeof(struct sockaddr);
	
	int fd = ::accept(this->sockfd, &addr, &addrlen);
	if (fd == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	
	// Make address string
	ip.clear();
	char* buf = nullptr;
	struct sockaddr_in* addr_in;
	struct sockaddr_in6* addr_in6;
	
	switch(addr.sa_family)
	{
		case AF_INET:
			addr_in = reinterpret_cast<struct sockaddr_in*>(&addr);
			buf = new char[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(addr_in->sin_addr), buf, INET_ADDRSTRLEN);
			break;
		case AF_INET6:
			addr_in6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
			buf = new char[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, &(addr_in6->sin6_addr), buf, INET6_ADDRSTRLEN);
			break;
		default:
			throw std::runtime_error("Invalid address family");
			break;
	}
	ip.append(buf);
	delete[] buf;
	
	return tcp_socket(fd);
}