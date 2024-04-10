#ifndef INETWORK_H_
#define INETWORK_H_

#include <vector>
// class tương tác với kết nối mạng trong một ứng dụng
class INetwork
{
public:
    // Hàm hủy ảo, đảm bảo rằng các lớp con sẽ được hủy đúng cách khi chúng được xóa thông qua một con trỏ cơ sở INetwork.
    virtual ~INetwork() = default;
    // Phương thức ảo để gửi dữ liệu thông qua kết nối mạng.
    virtual int send(const std::vector<char> &msg) = 0;
    // Phương thức ảo để nhận dữ liệu từ kết nối mạng.
    virtual int receive() = 0;
    // Phương thức ảo để thử kết nối đến một máy chủ hoặc thiết bị mạng
    virtual void tryConnection() = 0;
    // Phương thức ảo để ngắt kết nối với máy chủ hoặc thiết bị mạng
    virtual bool disconnect() = 0;
    //  Phương thức ảo để kiểm tra xem kết nối đang hoạt động hay không
    virtual bool isConnected() = 0;
    // Phương thức ảo để thiết lập trạng thái của kết nối
    virtual void setIsConnected(bool connected) = 0;
    // Phương thức ảo để chạy các hoạt động mạng, chẳng hạn như lắng nghe và xử lý dữ liệu
    virtual void run() = 0;
};

#endif