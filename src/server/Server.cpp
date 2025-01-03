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

class Server {
    static Dispatcher dispatcher;

  public:
    static void session(asio::ip::tcp::socket socket) {
        try {
            beast::flat_buffer buffer;

            // Read the HTTP request
            http::request<http::string_body> req;
            http::read(socket, buffer, req);

            // Prepare the HTTP response
            std::unique_ptr<http::response<http::string_body>> res =
                dispatcher.handleRequest(req);

            // Send the response
            http::write(socket, *res);

            // Close the connection
            socket.shutdown(asio::ip::tcp::socket::shutdown_send);

            std::cout << "Shut down the socket" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Session error: " << e.what() << std::endl;
        }
    }

    static void start_server() {
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
    }
};

Dispatcher Server::dispatcher = Dispatcher();

void server::start_server() { Server::start_server(); };
