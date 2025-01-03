#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <string>
#include <vector>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

class Dispatcher {
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
    Games games;
};
