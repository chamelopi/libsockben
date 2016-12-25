#include "abstract_socket.h" 

namespace ben
{
	template<>
	abstract_socket<tcp>::~abstract_socket()
	{
		if (!this->closed)
		{
			// No error handling here. If the user wishes a exception, he should
			// call socket.close() manually
			::close(this->sockfd);
		}
	}


	template<>
	void abstract_socket<tcp>::sendln(std::string& line)
	{
		if (this->closed) throw std::logic_error("Socket already closed");
		
		ssize_t size = ::send(this->sockfd, (void*)line.c_str(), line.size(), 0);
		if (size == -1)
		{
			throw std::runtime_error(strerror(errno));
		}
		
		if (::send(this->sockfd, (void*)"\n", 1, 0) == -1)
		{
			throw std::runtime_error(strerror(errno));
		}
	}

	template<>
	void abstract_socket<tcp>::recvln(std::string& line)
	{
		if (this->closed) throw std::logic_error("Socket already closed");
		
		char buf;
		line.clear();
		do
		{
			if (::recv(this->sockfd, (void*)&buf, sizeof(buf), 0) == -1)
			{
				throw std::runtime_error(strerror(errno));
			}
			line.append(&buf, 1);
		}
		while(buf != '\n');
	}


	template<>
	void abstract_socket<tcp>::recv(void* buf, size_t len)
	{
		if (this->closed) throw std::logic_error("Socket already closed");
		
		if (::recv(this->sockfd, buf, len, 0) == -1)
		{
			throw std::runtime_error(strerror(errno));
		}
	}


	template<>
	void abstract_socket<tcp>::send(const void* buf, size_t len)
	{
		if (this->closed) throw std::logic_error("Socket already closed");
		
		if (::send(this->sockfd, buf, len, 0) == -1)
		{
			throw std::runtime_error(strerror(errno));
		}
	}

	template<>
	void abstract_socket<tcp>::close()
	{
		if (!this->closed)		
		{
			this->closed = true;
			
			if (::close(this->sockfd) == -1)
			{
				// Note: If this exception is thrown, the socket object is in an
				// undefined state, and should not be used further!
				throw std::runtime_error(strerror(errno));
			}
		}
		else
		{
			throw std::logic_error("Socket already closed");
		}
	}
	
}