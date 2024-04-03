#ifndef BOOSTNETWORK_H_
#define BOOSTNETWORK_H_
#include <string>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind/bind.hpp>
#include "INetwork.h"
class BoostNetwork : public INetwork
{
public:
    // Constructor with default host and port
    BoostNetwork(boost::asio::io_service &io_service, boost::asio::ssl::context &context);

    // Constructor with specified host and port
    BoostNetwork(const std::string &port, const std::string &host, boost::asio::io_service &io_service, boost::asio::ssl::context &context);

    // Send data
    int send(const std::vector<char> &msg);

    // Reset connection
    void resetConnection();

    // Receive data
    int receive();

    // Handle handshake
    void handle_handshake(const boost::system::error_code &error);

    // Handle connection
    void handle_connect(const boost::system::error_code &error);

    // Attempt connection
    void tryConnection();

    // Disconnect
    bool disconnect();

    // Run IO service
    void run();

private:
    std::string _port;
    std::string _host;
    boost::asio::io_service _io_service;
    std::unique_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> _client;
    bool _isConnected;
};

#endif // BOOSTNETWORK_H_
