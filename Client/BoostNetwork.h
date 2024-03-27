#pragma once

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <thread>

class BoostNetwork
{
public:
    BoostNetwork(boost::asio::io_service& io_service, boost::asio::ssl::context &context);
    BoostNetwork(const std::string& port, const std::string& host, boost::asio::io_service& io_service, boost::asio::ssl::context &context);

    int send(const std::vector<char>& msg);
    void resetConnection();
    int receive();
    void handle_handshake(const boost::system::error_code& error);
    void handle_connect(const boost::system::error_code& error);
    void tryConnection();
    bool disconnect();
    void run();

private:
    std::string _port;
    std::string _host;
    boost::asio::io_service _io_service;
    std::unique_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> _client;
    bool _isConnected;
};