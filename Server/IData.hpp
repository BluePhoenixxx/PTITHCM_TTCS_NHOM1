#ifndef IDATA_HPP_
#define IDATA_HPP_

#include <memory>
#include <vector>

using namespace std;

class IData{
    public:
        //Các phương thức trừu tượng
        virtual ~IData() = default; //hủy đối tượng
        virtual void dump() const = 0; //in đối tượng 
        virtual string getData() const = 0; //getter
        virtual shared_ptr<IData> cloneObj(const vector<char> &data) = 0; //tạo bản sao từ đối tượng đầu vào
        virtual void feedObj(const vector<char> &data) = 0; //cung cấp dữ liệu cho đối tượng

};

#endif /* IDATA_HPP_ */