/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:39:26 by anolivei          #+#    #+#             */
/*   Updated: 2023/10/03 18:32:10 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(void) : _port(80), _server(NULL)
{
	createSocketTCP();
	configSocketAddress();
	bindSocketToAddress();
	waitConnection();
	return ;
}

Socket::Socket(int port, Server server, std::set<int> portsAccept) : _port(port), _server(server), _portsAccept(portsAccept)
{
	createSocketTCP();
	configSocketAddress();
	bindSocketToAddress();
	waitConnection();
	return ;
}

Socket::Socket(const Socket& obj)
{
	*this = obj;
	return ;
}

Socket::~Socket(void)
{
	this->closeClientFd();
	this->closeServerFd();
	return ;
}

Socket& Socket::operator=(const Socket& obj)
{
	if (this != &obj)
	{
		this->_port = obj._port;
		this->_server_fd = obj._server_fd;
		this->_client_fd = obj._client_fd;
		this->_addrlen = obj._addrlen;
		this->_address = obj._address;
		this->_server = obj._server;
		this->_HandleRequest = obj._HandleRequest;
		this->_serversMap = obj._serversMap;
		this->_portsAccept = obj._portsAccept;
	}
	return (*this);
}

void	Socket::setHandleRequest(HandleRequest HandleRequest)
{
	this->_HandleRequest = HandleRequest;
}

HandleRequest	Socket::getHandleRequest(void)
{
	return (this->_HandleRequest);
}

void	Socket::createSocketTCP(void)
{
	int opt = 1;
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int));
}

void	Socket::configSocketAddress(void)
{
	this->_addrlen = sizeof(this->_address);
	memset(&this->_address, 0, sizeof(this->_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(this->_port);
}

void	Socket::bindSocketToAddress(void)
{
	bind(
		this->_server_fd,
		(struct sockaddr *)&this->_address,
		sizeof(this->_address)
	);
}

void	Socket::waitConnection(void)
{
	int queue = 100;
	listen(this->_server_fd, queue);
}

int	Socket::getServerFd(void) const
{
	return (this->_server_fd);
}

void	Socket::acceptConnection(void)
{
	this->_client_fd = accept(this->_server_fd, (struct sockaddr *)&this->_address, (socklen_t*)&this->_addrlen);
	 std::set<int>::iterator it = _portsAccept.find(this->_port);
	if (it == _portsAccept.end()) {
		close(_client_fd);
		std::cout << "Invalid port" << std::endl;
		return;	
	}
	
		
	if (this->_client_fd == -1)
		throw (AcceptConnectionError()); 
	
	std::string response ;
	HandleRequest handleRequest;
	std::string header = handleRequest.receiveInformation(this->_client_fd);
	std::cout <<" receive----------" << header << " receive----------" << std::endl;

	

	
	
	handleRequest.readBuffer(header, this->_client_fd);

	std::cout << "headere" << header << std::endl;
	//handleRequest.receiveInformation(this->_client_fd);
	
	/*if (this->findField(header, "GET") == ""){
		HandleRequest.setBody(receiveInformation());
		std::cout << "new body ----------------" << std::endl;
		std::cout << HandleRequest.getBody();
		std::cout << "fim new body ----------------" << std::endl;
	}*/

	setHandleRequest(handleRequest);
	process(response, handleRequest, _server);
	
	send(_client_fd, response.c_str(), response.size(), 0);
	close(_client_fd);
	std::cout << "Closed connection" << std::endl;
}

std::string	Socket::findField(std::string src, std::string field)
{
	size_t pos = src.find(field);
	if (pos == std::string::npos)
		return "";
	pos += field.length();
	size_t end_pos = src.find("\r\n", pos);
	if (end_pos == std::string::npos)
	{
		end_pos = src.find(";", pos);
		if (end_pos == std::string::npos)
			return "";
	}
	if (src[pos] == '"')
		return src.substr(pos + 1, end_pos - pos - 2);
	return src.substr(pos, end_pos - pos);
}

bool	fdIsValid(int fd)
{
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

void	Socket::closeServerFd(void)
{
	if (fdIsValid(this->_server_fd))
		close(this->_server_fd);
}

void	Socket::closeClientFd(void)
{
	if (fdIsValid(this->_client_fd))
		close(this->_client_fd);
}

std::ostream&	operator<<(std::ostream& o, const Socket& i)
{
	o << "Socket: " << i.getServerFd();
	return o;
}

