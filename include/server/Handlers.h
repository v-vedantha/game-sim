#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <string>
#include <vector>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

class RequestHandler {
  public:
    virtual bool matches(const http::request<http::string_body> &req) = 0;

    virtual std::unique_ptr<std::string>
    handle(const http::request<http::string_body> &req) = 0;
};

class Dispatcher {
  public:
    /**
     * @brief Creates a dispatcher which dispatches requests to
     * allRequestHandlers
     *
     */
    Dispatcher();

    /**
     * @brief Dispatches the request to any handlers that can accept it.
     * Will fail the response if != 1 handler exists for that request.
     *
     * @param req
     * @param res
     */
    void handleRequest(http::request<http::string_body> &req,
                       http::response<http::string_body> &res);

  private:
    std::vector<std::shared_ptr<RequestHandler>> requestHandlers;
};
