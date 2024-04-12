#include "Parser.hpp"
#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

/* Hàm tạo Parser
+ Hàm tạo này nhận một chuỗi data là dữ liệu đầu vào cần phân tích.
+ Trích xuất loại dữ liệu từ data bằng cách gọi hàm getKeyData() 
với tham số "type=".
+ Dựa vào loại dữ liệu đã trích xuất, xác định phương thức phù hợp để phân 
tích dữ liệu bằng cách sử dụng một bản đồ _mapFeeder.
+ Nếu loại dữ liệu không được hỗ trợ, hàm tạo kết thúc; nếu không,
nó gọi phương thức phù hợp để phân tích dữ liệu. 
*/
Parser::Parser(const string &data) : _type(getKeyData("type=", data)){
    unordered_map<string, function<void(Parser &, const string &data)>> 
        _mapFeeder = {{"Mouse", &Parser::feedMouseData},
                    {"Status", &Parser::feedStatusData},
                    {"Keystroke", &Parser::feedKeystrokeData}};
    if(_mapFeeder.find(_type) == _mapFeeder.end())
        return;
    _mapFeeder[_type](*this, data);
            
}

/* getKeyData  
+ Nhận một chuỗi key và data, và trả về giá trị tương ứng với khóa từ dữ liệu.
+ Tìm vị trí của key trong data và trích xuất giá trị từ vị trí đó.
*/
string Parser::getKeyData(const string &key, const string &data){
    int startPos = data.find(key) + key.size();
    int endPos = data.find(key == "time=[" ? "]" : " ", startPos);
    return (data.substr(startPos, endPos - startPos));
}

/* feedMouseData, feedStatusData, feddKeystrokeData
+ Các phương thức này được gọi để phân tích dữ liệu dựa trên loại dữ liệu đã 
xác định từ hàm tạo.
+ Các phương thức này nhận dữ liệu từ data, trích xuất các thông tin 
cần thiết và lưu trữ chúng vào các thành viên của lớp Parser.
*/
void Parser::feedMouseData(const string &data){
    _time = getKeyData("time=[", data);
    _procName = getKeyData("procName=", data);
    _input = getKeyData("input=", data);
    istringstream(getKeyData("positionx=", data)) >> _pos_x;
    istringstream(getKeyData("positiony=", data)) >> _pos_y;
}

void Parser::feedStatusData(const string &data){
    _keyboardTrack = stringToBool(getKeyData("Keyboard=", data));
    _mouseClickTrack = stringToBool(getKeyData("MouseClick=", data));
    _mouseMoveTrack = stringToBool(getKeyData("MouseMove=", data));
    _pause = stringToBool(getKeyData("Pause=", data));
}

void Parser::feedKeystrokeData(const string &data){
    _time = getKeyData("time=[", data);
    _procName = getKeyData("ProcName=", data);
    _input = getKeyData("input=", data);
}

/* stringToBool
+ Nhận một chuỗi data và chuyển đổi nó thành một giá trị boolean.
+ Nếu data là "True", trả về true; nếu không, trả về false
*/ 
bool Parser::stringToBool(const string &data){
    return (data == "True" ? true : false);
}