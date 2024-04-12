#ifndef IINPUT_HPP_
#define IINPUT_HPP_

#include <utility>
// ghi nhận các dữ liệu từ chuột và bàn phím
class IInput
{
public:
    virtual int getKeyInput() = 0;

    virtual std::pair<int, int> getMouseInput() = 0;

    virtual int getTime() = 0;

    virtual char *getProcessus() = 0;
    // trả về con trỏ đến một chuỗi ký tự địa diện cho tên tiến trình
};

#endif // !IINPUT_HPP_