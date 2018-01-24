#ifndef BEN_ABS_SOCKET_H
#define BEN_ABS_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <cstdint>
#include <string>
#include <stdexcept>
#include <exception>
#include <sstream>
#include <iostream>

namespace ben
{
	/**
	 * Enumeration for protocol types supported by socket classes
	 */
	enum socket_protocol
	{
		tcp = SOCK_STREAM,
		udp = SOCK_DGRAM
	};


	/**
	 * Abstract base-class for object-oriented sockets.
	 * Methods throw exceptions instead of returning error values.
	 */
	template<enum socket_protocol protocol>
	class abstract_socket
	{
	protected:
		int sockfd;
		bool closed;

		// Internal constructor
		abstract_socket() : sockfd(-1), closed(false) {}
		virtual ~abstract_socket() noexcept;
	public:
		abstract_socket(int fd) : sockfd(fd), closed(false) {}

		void sendln(const std::string& line);
		void recvln(std::string& line);

		void send(const void* buf, size_t len);
		void recv(void* buf, size_t len);

		void close();
	};



	template<typename T, enum socket_protocol protocol>
	abstract_socket<protocol>& operator<<(abstract_socket<protocol>& sock, const T& val)
	{
		sock.send(&val, sizeof(val));
		return sock;
	}


	template<enum socket_protocol protocol>
	abstract_socket<protocol>& operator<<(abstract_socket<protocol>& sock, const std::string& val)
	{
		sock.send(val.c_str(), val.size());
		return sock;
	}


	template<typename T, enum socket_protocol protocol>
	abstract_socket<protocol>& operator>>(abstract_socket<protocol>& sock, T& val)
	{
		sock.recv(&val, sizeof(T));
		return sock;
	}


	template<enum socket_protocol protocol>
	abstract_socket<protocol>& operator>>(abstract_socket<protocol>& sock, std::string& val)
	{
		sock.recvln(val);
		return sock;
	}
}

#endif
