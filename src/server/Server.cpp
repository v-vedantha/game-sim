#include "Server.h"
#include "GameId.h"
#include "Games.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

std::unique_ptr<boost::json::object> handleCreateGame(Games &games) {

    GameId gameId = games.createGame();

    std::unique_ptr<boost::json::object> gameIdJson = gameId.to_json();
    return gameIdJson;
}

std::unique_ptr<http::response<http::string_body>>
Server::handleRequest(http::request<http::string_body> &req) {
    std::unique_ptr<http::response<http::string_body>> res =
        std::make_unique<http::response<http::string_body>>();

    res->version(req.version());
    res->keep_alive(req.keep_alive());
    res->result(http::status::ok);
    res->set(http::field::content_type, "text/plain");

    res->body() = boost::json::serialize(*handleCreateGame(games));

    res->prepare_payload();
    return res;
}
