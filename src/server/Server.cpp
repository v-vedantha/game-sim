#include "Server.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

void handle_request(http::request<http::string_body> req,
                    http::response<http::string_body> &res) {
    std::cout << "Handling the request" << std::endl;
    // Prepare the HTTP response
    res.version(req.version());
    res.keep_alive(req.keep_alive());
    res.result(http::status::ok);
    res.set(http::field::content_type, "text/plain");

    // Process the request
    if (req.method() == http::verb::get) {
        res.body() = "Hello! You sent a GET request.";
    } else if (req.method() == http::verb::post) {
        res.body() = "Hello! You sent a POST request with body: " + req.body();
    } else {
        res.result(http::status::bad_request);
        res.body() = "Unsupported HTTP method.";
    }
    std::cout << "Preparing payload" << std::endl;
    res.prepare_payload();
}

void session(asio::ip::tcp::socket socket) {
    try {
        std::cout << "Running session " << std::endl;
        beast::flat_buffer buffer;

        // Read the HTTP request
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        // Prepare the HTTP response
        http::response<http::string_body> res;
        handle_request(req, res);

        std::cout << "Request handled" << std::endl;

        // Send the response
        http::write(socket, res);

        std::cout << "wrote response" << std::endl;

        // Close the connection
        socket.shutdown(asio::ip::tcp::socket::shutdown_send);

        std::cout << "Shut down the socket" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Session error: " << e.what() << std::endl;
    }
}

int start_listener() {
    try {
        std::cout << "Starting the listener" << std::endl;
        // Create I/O context
        asio::io_context io_context;

        // Create a TCP acceptor
        asio::ip::tcp::acceptor acceptor(
            io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));

        std::cout << "Server is listening on http://localhost:8080\n";

        while (true) {
            // Accept a new connection
            std::cout << "vibes" << std::endl;
            asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::cout << "vibes" << std::endl;

            // Handle the session in a new thread
            std::thread(session, std::move(socket)).detach();
        }
    } catch (const std::exception &e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}

void Server::start() { start_listener(); }

void start_server() {
    std::cout << "Starting the server" << std::endl;
    Server server;
    server.start();
}
