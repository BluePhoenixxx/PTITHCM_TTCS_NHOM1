#ifndef DATAWRITER_HPP_
#define DATAWRITER_HPP_

#include <fstream>
#include <string>

#include <unordered_map>

using namespace std;

// Biến toàn cục là 1 chuỗi đại diện cho thư mục lưu trữ dữ liệu 
const string _dataDir = "dataDirectory";

//Cấu trúc lưu thông tin về thời gian và dữ liệu tuần tự
struct t_timeSmartLogs{
    int _startSequenceTime;
    int _currentSequenceTime;
    string _sequence;
};

class DataWriter{
public:
    DataWriter() = default;
    ~DataWriter() = default;
    /*  Phương thức ghi dữ liệu dựa vào loại dữ liệu nó sẽ gọi các phương
    thức riêng để ghi dữ liệu vào các tệp tin tương ứng*/
    void writeData(const string &host, const string &user,
                    const string &data);

private:
    //Lưu trữ các luồng tệp tin cho dữ liệu cơ bản
    unordered_map<string, ofstream> _fileStreamsBasic;
    
    //Lưu trữ các luồng tệp tin cho dữ liệu thông minh dựa trên thời gian
    unordered_map<string, ofstream> _fileStreamsTimeSmart;

    //Lưu trữ dữ liệu tuần tự dựa trên thời gian
    unordered_map<string, t_timeSmartLogs> _sequenceData;

    //Phương thức thử tạo thư mục nếu nó chưa tồn tại
    void tryInitDirectory(const string &host) const;

    //Phương thức để ghi dữ liệu cơ bản vào tập tin
    void writeBasicData(const string &host, const string &user, 
                        const string &data);
    
    //Phương thức để ghi dữ liệu thông minh dựa trên thời gian vào tệp tin
    void writeTimeBasedSmartData(const string &host, const string &user,
                                 const string &data);
    
    //Phương thức thiết lập lại dữ liệu tuần tự
    void resetSequenceData(const string &host, const string &user);

    //Phương thức riêng để cung cấp dữ liệu cho việc ghi tuần tự
    void feedSequenceWriter(const string &host, const string &user,
                            const string &data);

private:
    DataWriter(const DataWriter &cp) = default;
    DataWriter &operator=(const DataWriter &cp) = delete;

};

#endif /* DATAWRITER_HPP_ */