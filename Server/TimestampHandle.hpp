#ifndef TIMESTAMPHANDLE_HPP_
#define TNMESTAMPHANDLE_HPP_

#include <iostream>
#include <sstream>
#include <ctime>
#include <locale>
#include <string>
#include <iomanip>

using namespace std;

class TimestampHandle{
private:
    //Xóa để ngăn cản việc thể hiện và sao chép các đối tượng
    TimestampHandle() = delete; 
    TimestampHandle(const TimestampHandle &cp) = delete;
    TimestampHandle &operator=(const TimestampHandle &cp) = delete;
    ~TimestampHandle() = default;

public:
    /* Chuyển 1 timestamp (đc biểu diễn dưới dạng số nguyển) 
    thành dạng chuỗi "%c" đại diện cho biểu diễn ngày giờ */
    static string timeStampToString(const int &timeStamp){
        time_t t = timeStamp;
        char tmp[100];
        string res;

        if(strftime(tmp, sizeof(tmp), "%c", localtime(&t)))
            res = tmp;

        return (res);
    }

    /* 
        Chuyển đổi 1 chuỗi biểu diễn ngày giờ thành 1 timestamp 
        thành dạng số nguyên bằng cách sử dụng strptime */
    /*
        static int stringToTimestamp(const std::string &ct) {
        struct tm tm;
        strptime(ct.c_str(), "%c", &tm);
        return timegm(&tm);
        }  
    */

    /* 
        lưu ý: strptime() của <ctime> của phiên bản hiện tại đã ko còn 
        đc hỗ trợ nên ta phải dùng 1 pp khác để thay thế 
    */
    static int stringToTimestamp(const string &ct){
        istringstream ss(ct);
        tm tm = {};
        ss >> get_time(&tm, "%c");
        time_t time = mktime(&tm);
        
        return time;
    }

};

#endif /* TIMESTAMPHANDLE_HPP_ */