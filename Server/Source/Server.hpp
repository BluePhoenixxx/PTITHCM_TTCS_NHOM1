#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "Session.hpp"
#include <atomic>
#include <list>
#include <mutex>
#include <thread>

using namespace std;
extern mutex clientMutex;

class Server
{
    // Biến điều kiện đc sử dụng để theo dõi quá trình chấp nhận kết thúc của các luồng
    condition_variable _threadDeath;

    // Tham chiếu đến mutex đc sử dụng để đồng bộ hóa truy cập đến các danh sách các client
    mutex &_clientMutex;

    // Đối tượng acceptor đc sử dụng để chấp nhận kết nối từ client
    tcp::acceptor _acceptor;

    // Biến actomic boolean chỉ ra xem máy chủ đã kết thúc hoạt động hay chưa
    atomic<bool> _end;

    // Luồng đc sử dụng để kiểm tra và quản lý kết nối của các clients
    thread _clientCheck;

    // Danh sách các clients đc kết nối tới máy chủ
    list<shared_ptr<IClient>> &_clients;

    // Đối tượng context SSL đc sử dụng để thiết lập các kết nối SSL
    boost::asio::ssl::context _context;

public:
    Server(boost::asio::io_service &io_service, int port,
           list<shared_ptr<IClient>> &client, mutex &clientMutex);
    ~Server();

private:
    void startAccept();
    void handleAccept(Session::sessionPointer &newClient,
                      const boost::system::error_code &error);

private:
    Server(const Server &cp) = delete;
    Server &operator=(const Server &cp) = delete;
};

#endif /* SERVER_HPP_ */