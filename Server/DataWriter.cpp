#include "DataWriter.hpp"
#include "Parser.hpp"
#include "TimestampHandle.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>
#include <filesystem>

using namespace std;

/* writeData
+ Phương thức này gọi các phương thức tryInitDirectory(), writeBasicData() 
và writeTimeBasedSmartData() để ghi dữ liệu vào các tệp.
*/
void DataWriter::writeData(const string &host, const string &user,
                            const string &data){
    tryInitDirectory(host);
    writeBasicData(host, user, data);
    writeTimeBasedSmartData(host, user, data);

}

/* feedSequenceWriter
+ Phương thức này sử dụng một Parser để phân tích dữ liệu 
và kiểm tra nếu dữ liệu là loại "Keystroke".
+ Nếu là "Keystroke", nó kiểm tra và ghi dữ liệu dạng chuỗi thời gian thông minh.
+ Nếu không phải, phương thức kết thúc mà không làm gì cả.
*/
void DataWriter::feedSequenceWriter(const string &host, const string &user,
                                    const string &data){
    
    if(_sequenceData.find(host + user) == _sequenceData.end())
        resetSequenceData(host, user);
    
    Parser parser(data);
    
    if(parser._type != "Keystroke")
        return;
    
    if(_sequenceData[host + user]._startSequenceTime == 0)
        _sequenceData[host + user]._startSequenceTime = 
            TimestampHandle::stringToTimestamp(parser._time);

    if(_sequenceData[host + user]._currentSequenceTime == 0)
        _sequenceData[host + user]._currentSequenceTime = 
            TimestampHandle::stringToTimestamp(parser._time);

    if(_sequenceData[host + user]._currentSequenceTime + 1 >= 
        TimestampHandle::stringToTimestamp(parser._time)){
            _sequenceData[host + user]._sequence += ("+" + parser._input);
            _sequenceData[host + user]._currentSequenceTime = 
                TimestampHandle::stringToTimestamp(parser._time);
    }else{
        _fileStreamsTimeSmart[host + user]
            << "Data sequence: Start at ["+
                TimestampHandle::timeStampToString(
                    _sequenceData[host + user]._startSequenceTime) +
                "] -- End at [" +
                TimestampHandle::timeStampToString(
                    _sequenceData[host + user]._currentSequenceTime) +
                "]\nSequence: " + _sequenceData[host + user]._sequence + "\n";
        resetSequenceData(host, user);
    }
}

/* writeTimeBasedSmartData
+ Phương thức này kiểm tra nếu tệp thời gian thông minh cho host 
và user đã được mở. Nếu không, nó mở tệp đó.
+ Sau đó, nó gọi feedSequenceWriter() để ghi dữ liệu dạng chuỗi thời 
gian thông minh vào tệp.
*/
void DataWriter::writeTimeBasedSmartData(const string &host, const string &user,
                                        const string &data){
    auto it = _fileStreamsBasic.find(host + user);
    if (it == _fileStreamsTimeSmart.end())
        _fileStreamsTimeSmart[host + user] = 
            ofstream(_dataDir + "/" + host + "/" + user + "_TimeSmart.log");
    feedSequenceWriter(host, user, data);
}

/* writeBasicData
+ Phương thức này kiểm tra nếu tệp cơ bản cho host và user đã được mở. 
+ Nếu không, nó mở tệp đó và ghi dữ liệu vào tệp.
*/
void DataWriter::writeBasicData(const string &host, const string &user,
                                const string &data){
    auto it = _fileStreamsBasic.find(host + user);
    if(it == _fileStreamsBasic.end())
        _fileStreamsBasic[host + user] = 
            ofstream(_dataDir + "/" + user + "/" + user + ".log");
        _fileStreamsBasic[host + user] << (data + '\n');
}


/*
Lưu ý: Hàm mkdir(const *char) chỉ còn hỗ trợ 1 arg nên ta phải tìm giải pháp 
thay thế

void DataWriter::tryInitDirectory(const std::string &host) const {
  if (mkdir(_dataDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 &&
      errno != EEXIST)
    std::cerr << "cannot create host folder: " << std::strerror(errno)
              << std::endl;
  if (mkdir((_dataDir + "/" + host).c_str(),
            S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 &&
      errno != EEXIST) {
    std::cerr << "cannot create host folder: " << std::strerror(errno)
              << std::endl;
    throw std::runtime_error(strerror(errno));
  }
}
*/

/* tryInitDirectory
+ Phương thức này kiểm tra xem thư mục dữ liệu đã được khởi tạo chưa. 
Nếu chưa, nó tạo ra thư mục đó.
+ Tiếp theo, nó kiểm tra xem thư mục cho host đã được tạo chưa. 
Nếu chưa, nó tạo ra thư mục đó.
*/
void DataWriter::tryInitDirectory(const string &host) const{
    filesystem::path dataDirPath(_dataDir);

    //Kiểm tra nếu thư mục dữ liệu chưa tồn tại, tạo mới
    if (!filesystem::exists(dataDirPath)){
        try{
            filesystem::create_directory(dataDirPath);
        }catch (const filesystem::filesystem_error &err){
            cerr << "Failed to create data directory: " << err.what() << endl;
            throw;
        }
    }

    filesystem::path hostDirPath = dataDirPath / host;
    //Kiểm tra nếu thư mục cho host chưa tồn tại, tạo mới
    if (!filesystem::exists(hostDirPath)){
        try{
            filesystem::create_directory(hostDirPath);
        }catch(const filesystem::filesystem_error &err){
            cerr << "Failed to create host directory: " << err.what() << endl;
            throw;
        }
    }
}

/* resetSequenceData
+ Phương thức này đặt lại dữ liệu chuỗi cho host và user về giá trị ban đầu.
*/
void DataWriter::resetSequenceData(const string &host, const string &user){
    _sequenceData[host + user] = {0, 0, ""};
}
