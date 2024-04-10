#include "BoostNetwork.h"
#include <iostream>
//  khởi tạo BoostNetwork
BoostNetwork::BoostNetwork(boost::asio::io_service &io_service, boost::asio::ssl::context &context)
    : _port("4242"), _host("192.168.152.199"),
      _client(new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(_io_service, context)),
      _isConnected(false)
{
}
//
BoostNetwork::BoostNetwork(const std::string &port,
                           const std::string &host,
                           boost::asio::io_service &io_service,
                           boost::asio::ssl::context &context)
    : _port(port), _host(host), _client(new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(_io_service, context))
{
}
// gửi dữ liệu thông điệp qua Boost.asio
int BoostNetwork::send(const std::vector<char> &msg)
{
    _client->write_some(boost::asio::buffer(msg, msg.size()));
    return 0;
}
// thiết lập kết nối mạng
void BoostNetwork::resetConnection()
{
    // đặt lại trạng thái cho _io_service
    _io_service.reset();
    // thiết lập SSL qua giao thức sslv23
    boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
    // xác định máy chủ có kết nối ssl
    context.load_verify_file("server.crt");
    // đặt lại đối tượng client, một đối tượng socket TCP được tạo, sau đó được bao bọc bởi một stream SSL.
    _client.reset(new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(_io_service, context));
    // giả định rằng hàm này được sử dụng để thử kết nối lại với máy chủ.
    tryConnection();
    // dừng 1000ms để đợi đến khi đang kết nối đến server
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
}

int BoostNetwork::receive()
{
    try
    {
        // khởi tạo buff
        int l = 1024;
        std::vector<char> buf(l);
        boost::system::error_code error;
        // đọc dữ liệu từ socket vào buf
        _client->read_some(boost::asio::buffer(buf));
        int code = static_cast<int>(buf[0]);
        ;
        return (code);
    }
    catch (const std::exception &e)
    {
        resetConnection();
        return 0;
    }
}

void BoostNetwork::handle_handshake(const boost::system::error_code &error)
{
    // xử lý handshake SSL
    _isConnected = true;
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    if (error)
    {
        std::cout << "Handshake failed: " << error.message() << "\n";
        return resetConnection();
    }
}

void BoostNetwork::handle_connect(const boost::system::error_code &error)
{
    // thiết lập kết nối mạng
    if (!error)
    {
        _client->async_handshake(boost::asio::ssl::stream_base::client,
                                 boost::bind(&BoostNetwork::handle_handshake, this,
                                             boost::asio::placeholders::error));
    }
    else
    {
        std::cout << "Connect failed: " << error.message() << "\n";
        return resetConnection();
    }
}
// thử kết nối đến máy chủ thông qua giao thức TCP và SSL/TLS
void BoostNetwork::tryConnection()
{
    try
    {
        std::cout << "connection ..." << std::endl;
        _client->set_verify_mode(boost::asio::ssl::verify_peer);
        boost::asio::ip::tcp::resolver resolver(_io_service);
        boost::asio::ip::tcp::resolver::query query(_host.c_str(), _port.c_str());
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
        boost::asio::async_connect(_client->lowest_layer(), iterator,
                                   boost::bind(&BoostNetwork::handle_connect, this,
                                               boost::asio::placeholders::error));
        run();
    }
    catch (const std::exception &e)
    {
        return resetConnection();
    }
}
// hủy kết nối
bool BoostNetwork::disconnect()
{
    _io_service.stop();
    _client->lowest_layer().cancel();
    return (true);
}

// khởi chạy _io_service
void BoostNetwork::run()
{
    _io_service.run();
}