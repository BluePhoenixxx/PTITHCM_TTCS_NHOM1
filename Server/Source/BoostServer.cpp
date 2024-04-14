#include "BoostServer.hpp"
#include <boost/asio/ip/address.hpp>

using namespace std;

/* ~BoostServer
+ Phương thức hủy ~BoostServer được triển khai để dừng dịch vụ IO và 
chờ đợi cho luồng chạy của máy chủ. Nó gọi phương thức stop() của 
đối tượng _ioService để dừng các hoạt động IO đang chờ đợi. 
Sau đó, nó gọi join() trên luồng _running để chờ đợi cho luồng chạy 
của máy chủ kết thúc.
*/
BoostServer::~BoostServer(){
    _ioService.stop();
    _running.join();
}

/* startServer
+ Phương thức startServer được triển khai để khởi động máy chủ với cổng đã cho,
danh sách các client và mutex cho việc quản lý truy cập đến danh sách client. 
Nó tạo một đối tượng máy chủ mới bằng cách sử dụng std::make_unique và sau đó 
tạo một luồng mới để chạy dịch vụ IO bằng cách gọi run() trên đối tượng 
_ioService.
*/
void BoostServer::startServer(unsigned short port,
                            list<shared_ptr<IClient>> &clients,
                            mutex &clientMutex){
    _server = make_unique<Server>(_ioService, port, clients, clientMutex);
    _running = thread([this]() { _ioService.run(); });                         
}