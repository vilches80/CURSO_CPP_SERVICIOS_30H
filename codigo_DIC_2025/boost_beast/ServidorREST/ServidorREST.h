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

class ServidorREST
{
	net::io_context& ioc;
	tcp::acceptor acceptor;

public:
	ServidorREST(net::io_context&, unsigned int port);
	void run();
	~ServidorREST();

};

