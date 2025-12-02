#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;


class ServidorHTTP
{
	net::io_context& ioc;
	tcp::acceptor acceptor;

	void procesarPeticion(tcp::socket&);

public:
	ServidorHTTP(net::io_context&, unsigned int port);
	void run();
	~ServidorHTTP();

	
};

