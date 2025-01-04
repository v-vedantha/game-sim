#pragma once
#include "Rooms.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <string>
#include <vector>

namespace beast = boost::beast;
namespace http = beast::http;

/**
 * @brief Creates a game. This is only exposed for testing.
 *
 * @param games
 * @return std::unique_ptr<std::string>
 */
std::unique_ptr<boost::json::object> handleCreateGame(Rooms &rooms);

class Server {
  public:
    /**
     * @brief Dispatches the request to any handlers that can accept it.
     *
     * @param req
     * @return std::unique_ptr<http::response<http::string_body>> The response
     */
    std::unique_ptr<http::response<http::string_body>>
    handleRequest(http::request<http::string_body> &req);

  private:
    Rooms rooms;
};
