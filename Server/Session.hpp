#ifndef SESSION_HPP_
#define SESSION_HPP_

#include "IClient.hpp"
#include <array>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>

using namespace std;
using boost::asio::ip::tcp;

class Session : public enable_shared_from_this<Session>, public IClient{
    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

    //Một đối tượng socket SSL đc sử dụng để kết nối với client
    ssl_socket _socket;

    //id của phiên làm việc
    unsigned _id;

    //Bộ đệm nhận dữ liệu từ client
    array<char, 1024> _buffer;

    //Bộ đệm gửi trạng thái đến client
    array<int, 1> _stateBuf;

    //Biến boolean chỉ ra xem phiên làm việc đã kết thúc hay chưa
    bool _isDead;

    //Biến boolean chỉ ra xem phiên làm việc có sẵn để ghi dữ liệu hay ko
    bool _writeReady;

    //Tham chiếu đến điều kiện đc sử dụng để theo dõi sự kết thúc của phiên làm việc
    condition_variable &_threadDeath;

    //Hàng đợi để lưu trữ nhận đc từ client
    queue<vector<char>> _dataQueue;

public:
    ~Session() = default;

    typedef shared_ptr<Session> sessionPointer;

    static sessionPointer create(boost::asio::io_service &ioService,
                                boost::asio::ssl::context &contex,
                                condition_variable &threadDeath);

    ssl_socket::lowest_layer_type &getSocket();
    void start();
    bool isDead() const;
    void notifyDeath();
    void doRead();

    void sendState(int state) override final;
    vector<char> receiveData() override final;
    unsigned getId() const override final;
    bool dataAvailable() override final;
    bool writeReady() const override final;

private:
    Session(boost::asio::io_service &ioService, unsigned id, 
            boost::asio::ssl::context &context,
            condition_variable &threadDeath);
    Session(const Session &cp) = delete;
    Session &operator=(const Session &cp) = delete;

    void handleRead(const boost::system::error_code &error);
    void handleHandshake(const boost::system::error_code &error);
};

#endif /* SESSION_HPP_ */