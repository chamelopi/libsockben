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
	};
	
	
	/**
	 * Server socket base class
	 */
	template<enum socket_protocol protocol>
	class server_socket : public abstract_socket<protocol>
	{
	public:
		server_socket() : abstract_socket<protocol>(-1) {}
	};
	
	
	class tcp_socket : public socket<tcp>
	{
	public:
		tcp_socket(int sockfd) : socket<tcp>(sockfd) {}
		tcp_socket(const char* addr, const char* srvc);
		tcp_socket(std::string& addr, std::string& srvc) : tcp_socket(addr.c_str(), srvc.c_str()) {};
	};
	
	class tcp_server_socket : public server_socket<tcp>
	{
	public:
		// TODO: This currently only supports IPv4. Add IPv6 support
		tcp_server_socket(short port);
		// TODO: Add constructor that lets the user chose a local ip address
		
		tcp_socket accept();
		tcp_socket accept(std::string& ip);
	};
	
	
	class udp_socket : public socket<udp>
	{
		// TODO: Implement
	};
	
	class udp_server_socket : public server_socket<udp>
	{
		// TODO: Implement (only really binds to port)
	};
	
	// TODO: Implement stream operators
}

#endif