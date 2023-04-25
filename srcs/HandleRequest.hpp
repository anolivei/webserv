/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:37:17 by anolivei          #+#    #+#             */
/*   Updated: 2023/04/18 22:53:32 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_REQUEST_HPP
#define HANDLE_REQUEST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

class HandleRequest
{
	public:
		HandleRequest(void);
		HandleRequest(const HandleRequest& obj);
		virtual ~HandleRequest(void);

		HandleRequest&	operator=(const HandleRequest& obj);

		void	readBuffer(std::string buffer);

		std::string		getHost(void);
		std::string		getMethod(void);
		std::string		getBaseURL(void);
		std::string		getEndpoint(void);

	private:
		std::string	_method;
		std::string	_baseURL;
		std::string	_endpoint;
		std::string	_version;
		std::string	_host;
		int			_contentLength;
		std::string _body;

	protected:
};

std::ostream&	operator<<(std::ostream& o, const HandleRequest& i);

#endif
