#include "Server.h"
#include "RoomId.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;

std::unique_ptr<boost::json::object> handleCreateGame(Rooms &rooms) {

    RoomId roomId = rooms.createRoom();

    return roomId.to_json();
}

std::unique_ptr<http::response<http::string_body>>
Server::handleRequest(http::request<http::string_body> &req) {
    std::unique_ptr<http::response<http::string_body>> res =
        std::make_unique<http::response<http::string_body>>();

    res->version(req.version());
    res->keep_alive(req.keep_alive());
    res->result(http::status::ok);
    res->set(http::field::content_type, "text/plain");

    res->body() = boost::json::serialize(*handleCreateGame(rooms));

    res->prepare_payload();
    return res;
}
