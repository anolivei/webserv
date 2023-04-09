/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfigServer.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:32:15 by anolivei          #+#    #+#             */
/*   Updated: 2023/04/09 17:51:53 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfigServer.hpp"

LocationConfigServer::LocationConfigServer(void)
{
	std::cout
		<< "LocationConfigServer default constructor called"
		<< std::endl;
	return ;
}

LocationConfigServer::LocationConfigServer(const LocationConfigServer& obj)
{
	std::cout
		<< "LocationConfigServer copy constructor called"
		<< std::endl;
	*this = obj;
	return ;
}

LocationConfigServer::~LocationConfigServer(void)
{
	std::cout
		<< "LocationConfigServer destructor called"
		<< std::endl;
	return ;
}

LocationConfigServer& LocationConfigServer::operator=(const LocationConfigServer& obj)
{
	if (this != &obj)
	{
		this->_autoIndex = obj._autoIndex;
		this->_root = obj._root;
		this->_allowedMethods = obj._allowedMethods;
		this->_pagesIndex = obj._pagesIndex;
		this->_cgi = obj._cgi;
		
	}
	return (*this);
}

std::ostream&	operator<<(std::ostream& o, const LocationConfigServer& i)
{
	o << "something";
	return o;
}
