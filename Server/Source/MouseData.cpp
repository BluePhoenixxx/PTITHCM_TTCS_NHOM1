#include "MouseData.hpp"
#include "Protocol.hpp"
#include "TimestampHandle.hpp"
#include <cstring>
#include <iostream>

using namespace std;

/* MouseData
+ Khởi tạo đối tượng MouseData với các giá trị mặc định cho timestamp, 
vị trí chuột và loại click.
*/
MouseData::MouseData(): 
    _timestamp(0), _pos({0, 0}), _clickType(PTITKeyLogger::NONE) {}

/* MouseData
+ Constructor này chấp nhận một vector data chứa dữ liệu từ gói tin đến từ 
client.
+ Nó kiểm tra xem kích thước của data có đủ lớn không để chứa thông tin về 
timestamp, vị trí chuột và loại click không.
+ Nếu kích thước đủ lớn, nó sao chép thông tin timestamp, 
vị trí chuột và loại click từ data vào các biến tương ứng trong đối tượng 
MouseData.
+ Nó cũng sao chép tên tiến trình từ data vào _procName.
*/
MouseData::MouseData(const vector<char> &data){
    if (data.size() < sizeof(int) + sizeof(PTITKeyLogger::VALID_MOUSE_EVENT)){
        cerr << "Invalid size of packet for VALID_MOUSE_EVENT." << endl;
        return;
    }
    
    _timestamp = *(reinterpret_cast<const int *>(&data[sizeof(int)]));
    
    _pos = {
        *(reinterpret_cast<const int *>(
            &data[sizeof(int) + sizeof(_timestamp) + sizeof(_procName)])),
        
        *(reinterpret_cast<const int *>(
            &data[sizeof(int) + sizeof(_timestamp) + sizeof(_procName)
                                                       + sizeof(int)]))
    };

    _clickType = *(reinterpret_cast<const PTITKeyLogger::ClickType *>(
        &data[sizeof(int) + sizeof(_timestamp) + sizeof(_procName) 
                                                        + sizeof(int)]));

    memcpy(&_procName[0], &data[sizeof(int) + sizeof(_timestamp)], 
                                                        sizeof(_procName));
}

/* cloneObj
+ Phương thức này trả về một con trỏ shared_ptr mới cho một đối tượng 
MouseData được tạo từ dữ liệu data
*/
shared_ptr<IData> MouseData::cloneObj(const vector<char> &data){
    return (make_shared<MouseData>(data));
}

void MouseData::dump() const {}

/* getData
+ Phương thức này trả về một chuỗi đại diện cho dữ liệu từ gói tin chuột. 
Nó bao gồm thông tin về timestamp, tên tiến trình, loại click và vị trí chuột.
*/
string MouseData::getData() const{
    static unordered_map<PTITKeyLogger::ClickType, string> _clickName = {
        {PTITKeyLogger::NONE, "NONE"},
        {PTITKeyLogger::LEFT, "Lefy click"},
        {PTITKeyLogger::RIGHT, "Right click"},
        {PTITKeyLogger::OTHER, "Other button click"}
    };

    string tmpClickType = _clickType >= PTITKeyLogger::OTHER
                                    ? _clickName[PTITKeyLogger::OTHER]
                                    : _clickName[_clickType];

    return ("type=Mouse time=[" + TimestampHandle::timeStampToString(_timestamp) +
            + "] procName=" + _procName + " input=" + tmpClickType
            + " positionX=" + to_string(_pos.first)
            + " positionY=" + to_string(_pos.second));
}

/* feedObj
+ Phương thức này thực hiện một công việc tương tự như constructor
MouseData(const std::vector<char> &data). Nó cũng sao chép thông 
tin từ data vào các biến thành viên của đối tượng MouseData, 
bao gồm timestamp, vị trí chuột và loại click.
*/
void MouseData::feedObj(const vector<char> &data){
    if (data.size() < sizeof(int) + sizeof(PTITKeyLogger::VALID_MOUSE_EVENT)){
        cerr << "Invalid size of packet for VALID_MOUSE_EVENT." <<endl;
        return;
    }

    _timestamp = *(reinterpret_cast<const int *>(&data[sizeof(int)]));

    _pos = {
        *(reinterpret_cast<const int *>(
            &data[sizeof(int) + sizeof(_timestamp) + sizeof(_procName)])),
        
        *(reinterpret_cast<const int *>(
            &data[sizeof(int) + sizeof(_timestamp) + sizeof(_procName)
                                                       + sizeof(int)]))
    };

     _clickType = *(reinterpret_cast<const PTITKeyLogger::ClickType *>(
        &data[sizeof(int) + sizeof(_timestamp) + sizeof(_procName) 
                                                        + sizeof(int)]));

    memcpy(&_procName[0], &data[sizeof(int) + sizeof(_timestamp)], 
                                                        sizeof(_procName));
}
