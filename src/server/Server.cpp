#include "Server.h"
#include "Handlers.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace server;

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

std::unique_ptr<http::response<http::string_body>>
handle_request(http::request<http::string_body> req) {

    // Make a default response. Unique ptr because we want to return this
    // response without copying it.
    std::unique_ptr<http::response<http::string_body>> res =
        std::make_unique<http::response<http::string_body>>();

    std::cout << "Got a request" << std::endl;
    // Common amongst all types of responses.
    // If this is not the case in the future, we can break this abstraction.
    res->version(req.version());
    res->keep_alive(req.keep_alive());
    res->result(http::status::ok);
    res->set(http::field::content_type, "text/plain");

    Dispatcher dispatcher;
    dispatcher.handleRequest(req, *res);

    res->prepare_payload();
    return res;
}

void session(asio::ip::tcp::socket socket) {
    try {
        beast::flat_buffer buffer;

        // Read the HTTP request
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        // Prepare the HTTP response
        std::unique_ptr<http::response<http::string_body>> res =
            handle_request(req);

        // Send the response
        http::write(socket, *res);

        // Close the connection
        socket.shutdown(asio::ip::tcp::socket::shutdown_send);

        std::cout << "Shut down the socket" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Session error: " << e.what() << std::endl;
    }
}

void server::start_server() {
    try {
        // Create I/O context
        asio::io_context io_context;

        // Create a TCP acceptor
        asio::ip::tcp::acceptor acceptor(
            io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));

        std::cout << "Server is listening on http://localhost:8080\n";

        while (true) {
            // Accept a new connection
            asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Handle the session in a new thread
            std::thread(session, std::move(socket)).detach();
        }
    } catch (const std::exception &e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
};
