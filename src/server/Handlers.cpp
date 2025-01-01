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

class CreateGameHandler : public RequestHandler {
  public:
    CreateGameHandler() {}
    bool matches(const http::request<http::string_body> &req) override {
        return req.target() == "/hi" && req.method() == http::verb::post;
    }

    std::unique_ptr<std::string>
    handle(const http::request<http::string_body> &req) override {

        GameId gameId("hi"); // = games.createGame();

        boost::json::value gameIdJson = gameId.to_json();
        std::string gameIdAsString(boost::json::serialize(gameIdJson));

        return std::make_unique<std::string>(gameIdAsString);
    }
};

// This is technically a unique pointer but it is cleaner to treat it as a
// shared pointer because unique_ptr runs into some copying issues when
// iterating over the vector.

// The dispatcher also maintains references to the handlers in
// allRequestHandlers, but as these handlers are stateless, and just a place
// to store functions, this is fine.
Dispatcher::Dispatcher() {
    this->requestHandlers.push_back(std::make_shared<CreateGameHandler>());
}

void Dispatcher::handleRequest(http::request<http::string_body> &req,
                               http::response<http::string_body> &res) {

    bool requestHandled = false;
    for (auto &handler : requestHandlers) {
        bool handlerCanHandle = handler->matches(req);
        if (handlerCanHandle && !requestHandled) {
            res.body() = *(handler->handle(req));
            requestHandled = true;
        } else if (handlerCanHandle && requestHandled) {
            res.result(http::status::bad_request);
            res.body() = "Ambiguous request. Multiple handlers";
        }
    }
    if (!requestHandled) {
        res.result(http::status::bad_request);
        res.body() = "Unsupported HTTP method.";
    }
}
