#ifndef PASRER_HPP_
#define PARSER_HPP_

#include <string>

using namespace std;

class Parser{
public:
    Parser() = default;
    Parser(const string &data);
    ~Parser() = default;

public:
    string _type; //Loại định dữ liệu đc phân tích
    string _time; //Thời gian liên quan đến dữ liệu
    string _procName; //Tên quy trình
    string _input; //Dữ liệu đầu vào

    //Tọa độ x và y của chuột
    int _pos_x; 
    int _pos_y;

    //Các biến để theo dõi hoạt động bàn phím, click chuột, di chuyển chuột và tạm dừng
    bool _keyboardTrack;
    bool _mouseClickTrack;
    bool _mouseMoveTrack;
    bool _pause;

private:
    
    Parser(const Parser &cp) = delete;
    Parser &operator=(const Parser &cp) = delete;

    //Trích xuất dữ liệu liên quan đến khóa từ dữ liệu đầu vào
    string getKeyData(const string &key, const string &data);

    //Phương thức riêng để xử lý và trích xuất dữ liệu từ các loại dữ liệu khác nhau
    void feedMouseData(const string &data);
    void feedStatusData(const string &data);
    void feedKeystrokeData(const string &data);

    //Chuyển đổi giá trị kiểu chuỗi sang boolean
    bool stringToBool(const string &data);

};

#endif /* PARSER_HPP_ */