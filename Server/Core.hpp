#ifndef CORE_HPP_
#define CORE_HPP_

#include "BoostServer.hpp"
#include "CommandHandler.hpp"
#include "DataHandler.hpp"

using namespace std;

class Core{
    // Dùng để theo dõi trạng thái kết thúc của ứng dụng
    bool _quit;

    // Mutex được sử dụng để đồng bộ hóa truy cập đến danh sách các client.
    mutex _clientMutex;

    // Được sử dụng để quản lý máy chủ và giao tiếp mạng.
    unique_ptr<INetwork> _network;

    // Lưu trữ danh sách các client được kết nối đến máy chủ.
    list<shared_ptr<IClient>> _clients;

    // Xử lý dữ liệu được gửi và nhận từ client.
    DataHandler _dataHandler;

    // Xử lý các lệnh được nhập từ bàn điều khiển.
    CommandHandler _commandHandler;

    // Được sử dụng để chạy hệ thống xử lý lệnh trong nền.
    thread _commandThread;

public:
    Core();
    ~Core();

    void start(unsigned short port);

private:
    Core(const Core &cp) = default;
    Core &operator=(const Core &cp) = default;

};
#endif /* CORE_HPP_ */