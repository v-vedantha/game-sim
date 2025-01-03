#include "Handlers.h"
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

std::unique_ptr<std::string> handleCreateGame(Games &games) {

    GameId gameId = games.createGame();

    boost::json::value gameIdJson = gameId.to_json();
    std::string gameIdAsString(boost::json::serialize(gameIdJson));

    return std::make_unique<std::string>(gameIdAsString);
}

std::unique_ptr<http::response<http::string_body>>
Dispatcher::handleRequest(http::request<http::string_body> &req) {
    std::unique_ptr<http::response<http::string_body>> res =
        std::make_unique<http::response<http::string_body>>();

    std::cout << "Got a request" << std::endl;
    res->version(req.version());
    res->keep_alive(req.keep_alive());
    res->result(http::status::ok);
    res->set(http::field::content_type, "text/plain");

    res->body() = *handleCreateGame(games);

    res->prepare_payload();
    return res;
}
