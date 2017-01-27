#ifndef BEN_SOCKET_H
#define BEN_SOCKET_H

#include "abstract_socket.h"

namespace ben
{
	/**
	 * Client socket base class
	 */
	template<enum socket_protocol protocol>
	class socket : public abstract_socket<protocol>
	{
	public:
		socket(int sockfd) : abstract_socket<protocol>(sockfd) {}
		socket(const char* addr, const char* srvc);
		socket(std::string& addr, std::string& srvc) : socket(addr.c_str(), srvc.c_str()) {};
	};


	/**
	 * Server socket base class
	 */
	template<enum socket_protocol protocol>
	class server_socket : public abstract_socket<protocol>
	{
	public:
		server_socket() : abstract_socket<protocol>(-1) {}
		server_socket(short port);
	};


	class tcp_socket : public socket<tcp>
	{
	public:
		tcp_socket(int sockfd) : socket<tcp>(sockfd) {}
		tcp_socket(const char* addr, const char* srvc) : socket<tcp>(addr, srvc) {}
		tcp_socket(std::string& addr, std::string& srvc) : socket<tcp>(addr.c_str(), srvc.c_str()) {}
	};

	class tcp_server_socket : public server_socket<tcp>
	{
	public:
		// TODO: This currently only supports IPv4. Add IPv6 support
		tcp_server_socket(short port) : server_socket<tcp>(port) {}
		// TODO: Add constructor that lets the user choose a local ip address

		tcp_socket accept();
		tcp_socket accept(std::string& ip);
	};


	class udp_socket : public socket<udp>
	{
	public:
		udp_socket(int sockfd) : socket<udp>(sockfd) {}
		udp_socket(const char* addr, const char* srvc) : socket<udp>(addr, srvc) {}
		udp_socket(std::string& addr, std::string& srvc) : socket<udp>(addr.c_str(), srvc.c_str()) {}
	};

	class udp_server_socket : public server_socket<udp>
	{
	public:
		udp_server_socket(short port) : server_socket<udp>(port) {}
	};
}

#endif
