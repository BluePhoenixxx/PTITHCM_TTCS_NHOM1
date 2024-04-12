#include "Core.hpp"

using namespace std;

/* Core
+ Phương thức khởi tạo (Core::Core) khởi tạo các thành phần của lõi ứng dụng. 
Trong đó:
+ Biến _quit được khởi tạo là false, đánh dấu rằng ứng dụng chưa kết thúc.
+ Đối tượng _network được khởi tạo là một BoostServer, quản lý máy chủ và 
giao tiếp mạng.
+ Đối tượng _commandHandler được khởi tạo với danh sách clients (_clients), 
mutex của clients (_clientMutex) và biến _quit.
+ Một luồng _commandThread được tạo để chạy hệ thống xử lý lệnh, cho phép 
người dùng nhập lệnh từ bàn điều khiển và xử lý chúng.
*/
Core::Core() :
    _quit(false), _network(new BoostServer),
    _commandHandler(_clients, _clientMutex, _quit), _commandThread([this](){
        string line;
        while (_quit == false && getline(cin, line))
            _commandHandler.executeCommand(line);
        _clientMutex.lock();
        _quit = true;
        _clientMutex.unlock();
    }) {}

/* ~Core
+ giải phóng tài nguyên và kết thúc luồng xử lý lệnh.
*/
Core::~Core(){
    _clientMutex.lock();
    _clients.clear();
    _clientMutex.unlock();
    _commandThread.join();

}

/* start
+ Khởi động máy chủ thông qua _network->startServer.
+ Vòng lặp chạy trong khi ứng dụng chưa kết thúc (_quit == false).
+ Trong mỗi vòng lặp, nó kiểm tra xem có dữ liệu mới từ các client không. 
Nếu có, nó nhận dữ liệu và gửi đến đối tượng _dataHandler để xử lý.
*/
void Core::start(unsigned short port){
    _network->startServer(port, _clients, clientMutex);
    while(_quit == false){
        this_thread::sleep_for(chrono::microseconds(1));
        _clientMutex.lock();
    for(auto &it : _clients){
           if (it->dataAvailable()){
                vector<char> msg = it->receiveData();
                if(msg.size() < 4){
                    cerr << "Invalid Packet size (less than 4 bytes)." << endl;
                    continue;
                }
                _dataHandler.handleData(it->getId(), msg);
           }
        }
        _clientMutex.unlock();
    }
}