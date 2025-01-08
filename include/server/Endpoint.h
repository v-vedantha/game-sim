#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <string>
namespace beast = boost::beast;
namespace http = beast::http;

class Endpoint {

  public:
    virtual bool canHandle(std::string &uri, http::verb verb) = 0;

    /**
     * @brief Will set the result and body of the response.
     *
     * @param req
     * @param res
     */
    virtual void handle(const http::request<http::string_body> &req,
                        http::response<http::string_body> &res) = 0;
};
