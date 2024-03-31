#ifndef COMMONTDATASTRUCT_HPP_
#define COMMONDATASTRUCT_HPP_

#include "EnumRequestsTypes.hpp"
#include <chrono>
#include <string>

using namespace std;

// Vị để mouse tracking
typedef pair<int, int> Position;

/* HeaderData
+ Cấu trúc này chứa dữ liệu header, bao gồm mã yêu cầu và thời gian.
+ _requestCode là mã yêu cầu, được định nghĩa trong tệp EnumRequestsTypes.hpp.
+ _time là một thời điểm, 
    được biểu diễn bằng chrono::time_point<chrono::system_clock>, 
    lưu trữ thời gian khi dữ liệu được tạo ra.
*/
struct HeaderData{
    RequestCode _requestCode;
    chrono::time_point<chrono::system_clock> _time;
};

struct UserData{
    string _useId;
    string procName;
};

#endif /* COMMONDATASTRUCT_HPP_ */