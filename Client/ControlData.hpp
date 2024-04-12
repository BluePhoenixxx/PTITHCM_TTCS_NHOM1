#ifndef CONTROLDATA_HPP_
#define CONTROLDATA_HPP_

#include "WindowsInput.hpp"
#include "Status.hpp"
#include "SafeQueue.hpp"
#include <memory>
// tạo cấu trúc
struct ControlData
{
    bool _isConnected = false;                // kiểm tra kết nối mạng của client
    SafeQueue<std::shared_ptr<IInput>> _keys; // tạo một đối tượng hàng đợi chứa các con trỏ share_ptr IInput nhap tu ban phim
    Status _state;                            // trạng thái của kết nối mạng của client
};

#endif // !CONTROLDATA_HPP_