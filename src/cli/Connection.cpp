#include "Connection.h"
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using namespace cli;

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;

int Connection::sendMessage(const std::string &message) {
    try {
        // Create I/O context
        asio::io_context io_context;

        // Resolve localhost and port
        asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "8080");

        // Create and connect the socket
        asio::ip::tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        // Create HTTP request
        http::request<http::string_body> request(http::verb::post, "/hi", 11);
        request.set(http::field::host, "localhost");
        request.set(http::field::content_type, "text/plain");
        request.body() = "Hello, localhost!";
        request.prepare_payload();

        // Send the request
        http::write(socket, request);

        // Read the response
        beast::flat_buffer buffer;
        http::response<http::string_body> response;
        http::read(socket, buffer, response);

        // Print the response
        std::cout << response << std::endl;

        // Close the socket
        beast::error_code ec;
        socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
        if (ec && ec != beast::errc::not_connected) {
            throw beast::system_error(ec);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
