#include "Server.h"
#include "RoomId.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;

Server::Server() {
    auto roomsControllerEndpoints = roomsController.endpoints();
    endpoints.insert(endpoints.end(), roomsControllerEndpoints.begin(),
                     roomsControllerEndpoints.end());
}

std::unique_ptr<http::response<http::string_body>>
Server::dispatch(http::request<http::string_body> &req) {
    std::unique_ptr<http::response<http::string_body>> res =
        std::make_unique<http::response<http::string_body>>();

    res->version(req.version());
    res->keep_alive(req.keep_alive());
    res->set(http::field::content_type, "text/plain");

    std::cout << req.base() << std::endl;
    std::cout << req.target() << std::endl;

    bool reqHandled = false;
    for (auto endpoint : endpoints) {
        std::string target = req.target();
        if (endpoint->canHandle(target, req.method())) {
            endpoint->handle(req, *res);
            reqHandled = true;
            break;
        }
    }

    if (!reqHandled) {
        res->result(http::status::not_implemented);
        res->body() = "Error not implemented";
    }

    res->prepare_payload();
    return res;
}
