#ifndef BOOSTSERVER_HPP_
#define BOOSTSERVER_HPP_

#include "INetwork.hpp"
#include "Server.hpp"
#include <boost/asio.hpp>

using namespace std;

class BoostServer : public INetwork{
    /* Đối tượng io_service được sử dụng để quản lý các hoạt động đồng bộ 
    và không đồng bộ trên hệ thống I/O.*/
    boost::asio::io_service _ioService;

    /* Con trỏ đến đối tượng Server, là thành phần chính của máy chủ. 
    Đối tượng này được tạo và quản lý bởi BoostServer. */
    unique_ptr<Server> _server;

    /*  Luồng được sử dụng để chạy máy chủ. */
    thread _running;

public:
    BoostServer() = default;
    virtual ~BoostServer();

    void startServer(unsigned short port,
                    list<shared_ptr<IClient>> &clients,
                    mutex &clientMutex) final;

private:
    BoostServer(const BoostServer &cp) = delete;
    BoostServer &operator=(const BoostServer &cp) = delete;
};

#endif /* BOOSTSERVER_HPP_ */